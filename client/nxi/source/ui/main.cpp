#include <ui/main.hpp>
#include <ui/render/web.hpp>
#include <ui/window.hpp>
#include <nxw/tabbar.hpp>
#include <nxw/hbox_layout.hpp>

#include <nxi/core.hpp>

#include <QIcon>
#include <QPushButton>
#include <nxw/vbox_layout.hpp>
#include <QSplitter>

#include <ui/render/web_page.hpp>
#include <QtWidgets/QShortcut>
#include <nxw/tabwidget.hpp>
#include <include/ui/tree.hpp>
#include <include/ui/tab.hpp>
#include <QWebEnginePage>

namespace ui
{
    main::main(ui::window* window) :
        QWidget(window),
        nxi_core_ { window->nxi_core() },
        window_ { window }
    {
        // layouts
        auto main_layout = new nxw::vbox_layout;
        setLayout(main_layout);

        auto top_layout = new nxw::hbox_layout;
        auto tool_layout = new nxw::hbox_layout;
        auto middle_layout = new nxw::hbox_layout;
        auto bot_layout = new nxw::hbox_layout;
        left_layout_ = new nxw::vbox_layout;
        right_layout_ = new nxw::vbox_layout;

        main_layout->addLayout(top_layout);
        main_layout->addLayout(tool_layout);
        main_layout->addLayout(middle_layout);
        main_layout->addLayout(bot_layout);

        // menu button
        menu_button_ = new QPushButton(this);
        menu_button_->setObjectName("menu_button");
        menu_button_->setFixedSize(24, 24);
        menu_button_->setIcon(QIcon(":/image/menu"));
        menu_button_->setIconSize(QSize(16, 16));
        menu_button_->setCheckable(1);

        // engine
        engine_web_ = new ui::render::web(this);
        engine_web_->hide();

        // tabwidget
        tabbar_ = new nxw::tabbar(this);
        tabwidget_ = new nxw::tabwidget(this);
        tabwidget_->widget_ = engine()->widget();

        QObject::connect(tabbar_, &nxw::tabbar::currentChanged, tabwidget_, &nxw::tabwidget::on_change);

        // load tab page
        QObject::connect(tabbar_, &nxw::tabbar::currentChanged, [this](int index)
        {
            auto p = static_cast<ui::tab*>(tabwidget_->stack()->widget(index))->page_;

            qDebug() << "index " << index << "  load page  " << static_cast<render::web_page*>(p)->widget()->url();
            engine()->load(p);
        });


        // tree
        auto tree = new ui::tree(this);
        left_layout_->addWidget(tree);
        tree->setFixedWidth(200);
        connect(tree, &QTreeWidget::itemClicked, [this, tree](QTreeWidgetItem *item, int column){ tabwidget_->on_change(tree->indexOfTopLevelItem(item)); });

        // add tab
        auto tab_new = new QPushButton(this);
        tab_new->setObjectName("tab_new");
        tab_new->setFixedSize(24, 24);
        tab_new->setIcon(QIcon(":/image/tab_new"));
        tab_new->setIconSize(QSize(16, 16));

        connect(tab_new, &QPushButton::clicked, [this](){ nxi_core_.tabsystem().on_add(this); });

        connect(&nxi_core_.tabsystem(), &nxi::tabsystem::event_add, [this, tree](QWidget* source)
        {
            if (source == this)
            {
                auto t = tabwidget_->add<ui::tab>(this);
                tabbar_->addTab("test");

                auto item = new QTreeWidgetItem(tree);
                item->setText(0, "test");
                tree->addTopLevelItem(item);
            }
        });

        // fill layouts
        top_layout->addWidget(menu_button_);
        top_layout->addWidget(tabbar_);
        top_layout->addWidget(tab_new);
        top_layout->addStretch(1);
        middle_layout->addLayout(left_layout_);
        middle_layout->addLayout(right_layout_);


        right_layout_->addWidget(tabwidget_->stack());






        // test
        auto sc = new QShortcut(QKeySequence(Qt::Key_F11), this);
        connect(sc, &QShortcut::activated, [this]()
        {
            window_->main_swap(engine_web_->widget(), right_layout_);
        });

        auto sc2 = new QShortcut(QKeySequence("ctrl+T"), this);
        connect(sc2, &QShortcut::activated, [this]()
        {
            nxi_core_.tabsystem().on_add(this);
        });
    }

    main::~main()
    {}

    render::engine* main::engine()
    {
        return static_cast<render::engine*>(engine_web_);
    }
} // ui
