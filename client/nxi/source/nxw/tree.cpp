#include <nxw/tree.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <nxw/vbox_layout.hpp>
#include <nxw/tree.hpp>
#include <nxw/tree/page_item.hpp>

#include <QDebug>
#include <include/nxi/error.hpp>
#include <include/nxw/tree.hpp>
#include <include/nxw/menu.hpp>

#include <nxi/page/node.hpp>
#include <nxi/page/web.hpp>


#include <QStyledItemDelegate>
#include <QPainter>
#include <QtCore/QEvent>
#include <QMouseEvent>

/*
class tree_page_item_delegate : public QStyledItemDelegate {

public:

    explicit tree_page_item_delegate(QObject *parent = 0,
                         const QPixmap &closeIcon = QPixmap())
    : QStyledItemDelegate(parent)
    , m_closeIcon(closeIcon)
    {
        if(m_closeIcon.isNull())
        {
            m_closeIcon = QPixmap(":/button/window_close").scaledToWidth(16);
        }
    }

    QPoint closeIconPos(const QStyleOptionViewItem &option) const {
        return QPoint(option.rect.right() - m_closeIcon.width() - margin,
                      option.rect.center().y() - m_closeIcon.height()/2);
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const {
        QStyledItemDelegate::paint(painter, option, index);
        // Only display the close icon for top level items...


        painter->drawText(option.rect, "test");
        if(
            // ...and when the mouse is hovering the item
            // (mouseTracking must be enabled on the view)
        (option.state & QStyle::State_MouseOver))
        {
            painter->drawPixmap(closeIconPos(option), m_closeIcon);
            painter->drawText(option.rect, "test");
        }
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const
    {
        QSize size = QStyledItemDelegate::sizeHint(option, index);

        // Make some room for the close icon

            size.rwidth() += m_closeIcon.width() + margin * 2;
            size.setHeight(qMax(size.height(),
                                m_closeIcon.height() + margin * 2));

        return size;
    }

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index)
    {
        // Emit a signal when the icon is clicked
        if(!index.parent().isValid() &&
           event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

            QRect closeButtonRect = m_closeIcon.rect()
            .translated(closeIconPos(option));

            if(closeButtonRect.contains(mouseEvent->pos()))
            {
                qDebug() << "CLOSE";
            }
        }
        return false;
    }

signals:

private:
    QPixmap m_closeIcon;
    static const int margin = 2; // pixels to keep arount the icon

};
*/

namespace ui
{
    page_tree::page_tree(ui::core& ui_core) : ui_core_{ ui_core }
    {
        init_ui();
        init_data();
        init_event();
    }

    void page_tree::init_ui()
    {
        auto layout = new nxw::vbox_layout;

        setLayout(layout);

        setHeaderHidden(true);
        setStyleSheet("border: none;");
        //setRootIsDecorated(false);
        setContextMenuPolicy(Qt::CustomContextMenu);
        setEditTriggers(QAbstractItemView::EditKeyPressed);
        setSelectionMode(QAbstractItemView::ExtendedSelection);
        setFixedWidth(200);

        setDragEnabled(true);
        setAcceptDrops(true);
        setDropIndicatorShown(true);
        setDragDropMode(QAbstractItemView::DragDrop);
        setDefaultDropAction(Qt::MoveAction);
    }

    void page_tree::init_data()
    {
        // load stored page
        for (const auto& page : ui_core_.nxi_core().page_system().get())
        {
            auto page_item = new ui::tree_page_item(this, page->id());
            page_item->setText(0, page->name());
            page_items_.emplace(page->id(), page_item);
        }

        // connect pages
        for (const auto& [source_id, target_id] : ui_core_.nxi_core().page_system().connections())
        {
            qDebug() << "s: " << source_id << " t: " << target_id;

            if (source_id == 0) add(get(target_id));

            //ui_core_.nxi_core().page_system().get()
            /*
            qDebug() << "s: " << source_id << " t: " << target_id;
            auto source = get(source_id);
            auto target = get(target_id);

            takeTopLevelItem(indexOfTopLevelItem(target));

            source->addChild(target);
             */
        }
    }

    void page_tree::init_event()
    {
        // tree option menu
        connect(this, &ui::page_tree::customContextMenuRequested, [this](const QPoint& point)
        {
            unsigned int source_id = 0;

            auto item = itemAt(point);
            if (item) source_id = static_cast<ui::tree_page_item*>(item)->id();

            auto menu = new nxw::menu(this);
            menu->add("new node", [this, source_id](){ ui_core_.nxi_core().page_system().add<nxi::page_node>(source_id); });
            menu->add("new web_page", [this, source_id](){ ui_core_.nxi_core().page_system().add<nxi::web_page>(source_id); });
            menu->exec();
        });

        // page_system::event_add
        // page_node
        connect(&ui_core_.nxi_core().page_system(), qOverload<nxi::page_node&, nxi::page_id>(&nxi::page_system::event_add), this, [this](nxi::page_node& page, nxi::page_id source_id)
        {
            auto page_item = add(page, source_id);
            page_item->setIcon(0, QIcon(":/image/node"));
        });

        // web_page
        connect(&ui_core_.nxi_core().page_system(), qOverload<nxi::web_page&, nxi::page_id>(&nxi::page_system::event_add), this, [this](nxi::web_page& page, nxi::page_id source_id)
        {
            auto page_item = add(page, source_id);
            page_item->setIcon(0, QIcon(":/image/network"));

            connect(&page, &nxi::web_page::event_update_icon, [page_item](const QIcon& icon)
            {
                page_item->setIcon(0, icon);
            });
        });

        // item click
        connect(this, &QTreeWidget::itemClicked, [this](QTreeWidgetItem* base_item, int)
        {
            auto item = static_cast<ui::tree_page_item*>(base_item);

            //item->change();
            // ui_core_.nxi_core().page_system().change<nxi::web_page>(id());
            ui_core_.nxi_core().page_system().focus(item->id());
        });
    }

    ui::tree_page_item* page_tree::add(nxi::page& page, nxi::page_id source_id)
    {
        auto page_item = new ui::tree_page_item(this, page.id());
        page_item->setText(0, page.name());

        page_items_.emplace(page.id(), page_item);

        if (source_id == 0) add(page_item);
        else
        {
            // get source item
            auto source_item = get(source_id);
            add(page_item, source_item);
        }

        // page update
        connect(&page, &nxi::page::event_update_name, [page_item](const QString& name)
        {
            page_item->setText(0, name);
        });

        return page_item;
    }

    void page_tree::add(tree_item* item)
    {
        //setItemDelegate(new tree_page_item_delegate{this});
        addTopLevelItem(item);
    }

    void page_tree::add(tree_item* item, tree_item* source_item)
    {
        source_item->addChild(item);
    }

    tree_item *page_tree::current_item() const
    {
        return static_cast<ui::tree_item*>(currentItem());
    }

    tree_item* page_tree::get(nxi::page_id id) const
    {
        assert(page_items_.count(id));

        return page_items_.at(id);
    }
} // nxw