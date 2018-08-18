#include <nxw/tree.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <QPushButton>

#include <nxw/vbox_layout.hpp>
#include <nxw/tree.hpp>
#include <nxw/tree/page_item.hpp>
#include <include/nxw/tree.hpp>

#include <QDebug>
namespace nxw
{
    tree::tree(ui::core& ui_core) :
        m_ui_core { ui_core }
    {
        auto layout = new nxw::vbox_layout;

        setLayout(layout);

        auto btn = new QPushButton(this);
        btn->setText("add web_page");
        connect(btn, &QPushButton::clicked, this, [this]()
        {
            m_ui_core.nxi_core().page_system().add(nxi::web_page{});
        });
        layout->addWidget(btn);

        auto btn_e = new QPushButton(this);
        btn_e->setText("add explorer_page");
        connect(btn_e, &QPushButton::clicked, this, [this]()
        {
            m_ui_core.nxi_core().page_system().add(nxi::explorer_page{});
        });
        layout->addWidget(btn_e);

        m_tree = new QTreeWidget(this);
        m_tree->setHeaderHidden(true);
        m_tree->setStyleSheet("border: none;");
        //m_tree->setRootIsDecorated(false);
        m_tree->setContextMenuPolicy(Qt::CustomContextMenu);
        m_tree->setEditTriggers(QAbstractItemView::EditKeyPressed);
        setFixedWidth(200);

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

        // page added
        connect(&m_ui_core.nxi_core().page_system(), QOverload<nxi::web_page&>::of(&nxi::page_system::event_add), this, [this](nxi::web_page& page)
        {
            auto page_item = new nxw::tree_page_item(this, page.id);
            page_item->setText(0, QString::fromStdString(page.url));
            m_page_items.emplace(page.id, page_item);
            add(page_item);
        });

        connect(&m_ui_core.nxi_core().page_system(), QOverload<nxi::explorer_page&>::of(&nxi::page_system::event_add), this, [this](nxi::explorer_page& page)
        {
            auto page_item = new nxw::tree_page_item(this, page.id);
            page_item->setText(0, QString::fromStdString(page.path));
            m_page_items.emplace(page.id, page_item);
            add(page_item);
        });

        connect(&m_ui_core.nxi_core().page_system(), QOverload<const nxi::web_page&>::of(&nxi::page_system::event_update), this,
        [this](const nxi::web_page& page)
        {
            //m_page_items[page.id]->setText(0, QString::fromStdString(page.url));
        });
    }

    void tree::add(tree_item* item)
    {
        m_tree->addTopLevelItem(item);
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