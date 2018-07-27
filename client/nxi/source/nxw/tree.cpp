#include <nxw/tree.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <QPushButton>

#include <QVBoxLayout>

namespace nxw
{
    tree_item::tree_item(int id, tree_item* parent) : id_{id}
    {

    }

    tree::tree(ui::core& ui_core) :
        m_ui_core { ui_core }
    {
        auto layout = new QVBoxLayout;

        setLayout(layout);

        auto btn = new QPushButton(this);
        btn->setText("add");
        btn->show();
        connect(btn, &QPushButton::clicked, this, [this]()
        {
            //auto wp = nxi::web_page;
            m_ui_core.nxi_core().page_system().add({});
            //m_ui_core.interface_system().load(web_page);
        });
        layout->addWidget(btn);

        m_tree = new QTreeWidget(this);
        m_tree->setHeaderHidden(1);
        m_tree->setStyleSheet("border: none;");
        m_tree->setRootIsDecorated(false);
        m_tree->setContextMenuPolicy(Qt::CustomContextMenu);
        m_tree->setEditTriggers(QAbstractItemView::EditKeyPressed);
        m_tree->setFixedWidth(200);

        m_tree->setDragEnabled(1);
        m_tree->setAcceptDrops(1);
        m_tree->setDropIndicatorShown(1);
        m_tree->setDragDropMode(QAbstractItemView::DragDrop);
        m_tree->setDefaultDropAction(Qt::MoveAction);

        layout->addWidget(m_tree);

        // on click > tab change
        connect(m_tree, &QTreeWidget::itemClicked, [this](QTreeWidgetItem* item, int)
        {
            QModelIndex index = item->treeWidget()->currentIndex();
            auto item_id = static_cast<tree_item*>(item)->id();
            m_ui_core.page_system().change(item_id);
        });

        auto e = new tree_item(0);
        e->setText(0, "Web");
        m_tree->addTopLevelItem(e);

        connect(&m_ui_core.nxi_core().page_system(), &nxi::page_system::event_add, this, [this](nxi::web_page page)
        {
            auto e = new tree_item(page.id);
            e->setText(0, "test");
            m_tree->addTopLevelItem(e);
        });
    }

} // nxw