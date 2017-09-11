#include <ui/tree.hpp>
#include <ui/tree/nex_item.hpp>
#include <ui/tab.hpp>

#include <QTabBar>
#include <QHBoxLayout>
#include <QSplitter>
#include <QDebug>

namespace ui
{
    tree::tree(ui::tab* tab) :
        QTreeWidget(tab),
        tab_(tab)
    {
        setHeaderHidden(1);
        setStyleSheet("border: none;");

        setContextMenuPolicy(Qt::CustomContextMenu);

        setIndentation(15);
        setEditTriggers(QAbstractItemView::EditKeyPressed);

        // drag & drop
        setDragEnabled(1);
        setAcceptDrops(1);
        setDropIndicatorShown(1);
        setDragDropMode(QAbstractItemView::DragDrop);
        setDefaultDropAction(Qt::MoveAction);

        QObject::connect(this, &QTreeWidget::itemExpanded, this, &tree::on_item_expand);
        QObject::connect(this, &QTreeWidget::customContextMenuRequested, this, &tree::on_item_option);
        QObject::connect(tab_, &tab::event_connexion_connect, this, &tree::on_connexion_connect, Qt::QueuedConnection);
    }

    tree::~tree() {}

    void tree::item_add(tree_item* item)
    {
        this->addTopLevelItem(item);
    }


    void tree::on_item_expand(QTreeWidgetItem* in_item)
    {
        auto item = static_cast<tree_item*>(in_item);
        item->list();
    }

    void tree::on_item_option(const QPoint& pos)
    {
        QTreeWidgetItem* in_item = itemAt(pos);
        if (in_item == nullptr) return;

        // item disabled
        if (!(in_item->flags() & Qt::ItemIsEnabled)) return;

        static_cast<tree_item*>(in_item)->option();
    }

    void tree::on_connexion_connect()
    {
        // tree
        tree_nex_item* server = new tree_nex_item(this);
        server->setText(0, tab().url().host().c_str());
        server->node(true);
        server->setIcon(0, QIcon(":/image/nex"));
        item_add(server);
    }

    ui::tab& tree::tab()
    {
        return *tab_;
    }
} // ui
