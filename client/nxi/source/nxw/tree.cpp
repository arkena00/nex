#include <nxw/tree.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <QPushButton>

#include <nxw/vbox_layout.hpp>
#include <nxw/tree.hpp>
#include <nxw/tree/page_item.hpp>
#include <include/nxw/tree.hpp>


namespace nxw
{
    tree::tree(ui::core& ui_core) :
        m_ui_core { ui_core }
    {
        auto layout = new nxw::vbox_layout;

        setLayout(layout);

        auto btn = new QPushButton(this);
        btn->setText("add");
        btn->show();
        connect(btn, &QPushButton::clicked, this, [this]()
        {
            m_ui_core.nxi_core().page_system().add({});
        });
        layout->addWidget(btn);

        m_tree = new QTreeWidget(this);
        m_tree->setHeaderHidden(true);
        m_tree->setStyleSheet("border: none;");
        //m_tree->setRootIsDecorated(false);
        m_tree->setContextMenuPolicy(Qt::CustomContextMenu);
        m_tree->setEditTriggers(QAbstractItemView::EditKeyPressed);
        m_tree->setFixedWidth(200);

        m_tree->setDragEnabled(true);
        m_tree->setAcceptDrops(true);
        m_tree->setDropIndicatorShown(true);
        m_tree->setDragDropMode(QAbstractItemView::DragDrop);
        m_tree->setDefaultDropAction(Qt::MoveAction);

        layout->addWidget(m_tree);

        // on click > tab change
        connect(m_tree, &QTreeWidget::itemClicked, [this](QTreeWidgetItem* item, int)
        {
            static_cast<tree_item*>(item)->load();
        });

        auto web_root = new nxw::tree_page_item(this, 0);
        web_root->setIcon(0, QIcon(":/image/nex"));
        web_root->setText(0, "Web");
        m_tree->addTopLevelItem(web_root);

        // page added
        connect(&m_ui_core.nxi_core().page_system(), &nxi::page_system::event_add, this, [web_root, this](nxi::web_page page)
        {
            auto page_item = new nxw::tree_page_item(this, page.id);
            page_item->setText(0, QString::fromStdString(page.url));
            web_root->addChild(page_item);
            m_page_items.emplace(page.id, page_item);
            //m_tree->addTopLevelItem(page_item);
        });

        connect(&m_ui_core.nxi_core().page_system(), &nxi::page_system::event_update, this,
        [this](const nxi::web_page& page)
        {
            m_page_items[page.id]->setText(0, QString::fromStdString(page.url));
        });
    }

    tree_item *tree::current_item() const
    {
        return static_cast<tree_item*>(m_tree->currentItem());
    }

    ui::core& tree::ui_core() const
    {
        return m_ui_core;
    }

} // nxw