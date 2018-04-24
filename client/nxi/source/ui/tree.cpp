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

        qRegisterMetaType<QVector<int>>();
        QObject::connect(this, &QTreeWidget::itemExpanded, this, &tree::on_item_expand);
        QObject::connect(this, &QTreeWidget::customContextMenuRequested, this, &tree::on_item_option);
        QObject::connect(tab_, &tab::event_connexion_connect, this, &tree::on_connexion_connect, Qt::QueuedConnection);

    }

    tree::~tree() {}


////////////////////////////////////////////////////////////////////////////////
////////////////////////             EVENT              ////////////////////////
////////////////////////////////////////////////////////////////////////////////
    void tree::on_item_expand(QTreeWidgetItem* in_item)
    {

    }

    void tree::on_item_option(const QPoint& pos)
    {

    }

    void tree::on_connexion_connect()
    {

    }


////////////////////////////////////////////////////////////////////////////////
////////////////////////               GET              ////////////////////////
////////////////////////////////////////////////////////////////////////////////

    ui::tab& tree::tab()
    {
        return *tab_;
    }
} // ui
