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


namespace ui
{
    page_tree::page_tree(ui::core& ui_core) : ui_core_{ ui_core }
    {
        auto layout = new nxw::vbox_layout;

        setLayout(layout);
        
        setHeaderHidden(true);
        setStyleSheet("border: none;");
        //setRootIsDecorated(false);
        setContextMenuPolicy(Qt::CustomContextMenu);
        setEditTriggers(QAbstractItemView::EditKeyPressed);
        setFixedWidth(200);

        setDragEnabled(true);
        setAcceptDrops(true);
        setDropIndicatorShown(true);
        setDragDropMode(QAbstractItemView::DragDrop);
        setDefaultDropAction(Qt::MoveAction);

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
        connect(&ui_core_.nxi_core().page_system(), qOverload<nxi::page_node&, unsigned int>(&nxi::page_system::event_add), this, [this](nxi::page_node& page, unsigned int source_id)
        {
            add(page, source_id);
        });

        connect(&ui_core_.nxi_core().page_system(), qOverload<nxi::web_page&, unsigned int>(&nxi::page_system::event_add), this, [this](nxi::web_page& page, unsigned int source_id)
        {
            add(page, source_id);
        });

        // item click
        connect(this, &QTreeWidget::itemClicked, [this](QTreeWidgetItem* base_item, int)
        {
            auto item = static_cast<ui::tree_page_item*>(base_item);

            item->change();
            // ui_core_.nxi_core().page_system().change<nxi::web_page>(id());
            ui_core_.nxi_core().page_system().change(item->id());
        });

        /*// on click > tab change
        connect(m_tree, &QTreeWidget::itemClicked, [this](QTreeWidgetItem* item, int)
        {
            static_cast<tree_item*>(item)->load();
        });

        // page added
        connect(&m_ui_core.nxi_core().page_system(), QOverload<nxi::web_page&>::of(&nxi::page_system::event_add), this, [this](nxi::web_page& page)
        {

            auto page_item = new nxw::tree_page_item(this, page.id);
            page_item->setText(0, QString::fromStdString(page.url));
            page_items_.emplace(page.id, page_item);
            add(page_item);
        });

        connect(&m_ui_core.nxi_core().page_system(), QOverload<nxi::explorer_page&>::of(&nxi::page_system::event_add), this, [this](nxi::explorer_page& page)
        {
            auto page_item = new nxw::tree_page_item(this, page.id);
            page_item->setText(0, QString::fromStdString(page.path));
            page_items_.emplace(page.id, page_item);
            add(page_item);
        });

        connect(&m_ui_core.nxi_core().page_system(), QOverload<const nxi::web_page&>::of(&nxi::page_system::event_update), this,
        [this](const nxi::web_page& page)
        {
            //page_items_[page.id]->setText(0, QString::fromStdString(page.url));
        });

         */
    }

    void page_tree::add(const nxi::page& page, unsigned int source_id)
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
    }

    void page_tree::add(tree_item* item)
    {
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

    tree_item* page_tree::get(unsigned int id) const
    {
        assert(page_items_.count(id));

        return page_items_.at(id);
    }
} // nxw