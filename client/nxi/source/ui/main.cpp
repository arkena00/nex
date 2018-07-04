#include <ui/main.hpp>
#include <ui/render/web.hpp>
#include <ui/tabdata.hpp>
#include <ui/tabtree.hpp>
#include <ui/window.hpp>

#include <nxi/window_system.hpp>

#include <nxw/tabbar.hpp>
#include <nxw/hbox_layout.hpp>
#include <nxw/shortcut.hpp>

#include <nxi/core.hpp>

#include <QIcon>
#include <QPushButton>
#include <QShortcut>

namespace ui
{
    main::main(ui::window* window) :
        QWidget(window),
        nxi_core_ { window->nxi_core() },
        window_ { window }
    {
////////////////////////////////////////////////////////////////////////////////
////////////////////////             layouts            ////////////////////////
////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////

        // menu button
        menu_button_ = new QPushButton(this);
        menu_button_->setObjectName("menu_button");
        menu_button_->setFixedSize(24, 24);
        menu_button_->setIcon(QIcon(":/image/menu"));
        menu_button_->setIconSize(QSize(16, 16));
        menu_button_->setCheckable(1);

        QObject::connect(menu_button_, &QPushButton::clicked, [this]()
        {
        });

        // engine
        engine_web_ = new ui::render::web(this);
        engine_web_->hide();

////////////////////////////////////////////////////////////////////////////////
////////////////////////               tab              ////////////////////////
////////////////////////////////////////////////////////////////////////////////

        // tabwidget
        tabbar_ = new nxw::tabbar(this);
        tabtree_ = new ui::tabtree(this);
        tabwidget_ = new nxw::tabwidget(this, nxi_core_.tab_system());
        tabwidget_->tabchanger_add(tabbar_);
        tabwidget_->tabchanger_add(tabtree_);
        // tabdata
        auto tabdata = std::make_unique<ui::tabdata>();
        tabdata->engine = engine_web_;
        tabwidget_->data_add(std::move(tabdata));

        // add tab
        auto tab_new = new QPushButton(this);
        tab_new->setObjectName("tab_new");
        tab_new->setFixedSize(24, 24);
        tab_new->setIcon(QIcon(":/image/tab_new"));
        tab_new->setIconSize(QSize(16, 16));

        connect(tab_new, &QPushButton::clicked, [this](){ nxi_core_.tab_system().on_add(tabwidget_); });

        // fill layouts
        top_layout->addWidget(menu_button_);
        top_layout->addWidget(tabbar_->widget());
        top_layout->addWidget(tab_new);
        top_layout->addStretch(1);
        middle_layout->addLayout(left_layout_);
        middle_layout->addLayout(right_layout_);




        left_layout_->addWidget(tabtree_->widget());
        right_layout_->addWidget(tabwidget_->widget());


        // shortcut
        shortcut_ = new nxw::shortcut(this);

        // test
        auto sc = new QShortcut(QKeySequence(Qt::Key_F11), this);
        connect(sc, &QShortcut::activated, [this]()
        {
            window_->main_swap(engine_web_->widget(), right_layout_);
        });

        sc = new QShortcut(QKeySequence("ctrl+T"), this);
        connect(sc, &QShortcut::activated, [this]()
        {
            nxi_core_.tab_system().on_add(tabwidget_);
        });
        sc = new QShortcut(QKeySequence("ctrl+N"), this);
        connect(sc, &QShortcut::activated, [this]()
        {
            nxi::window w;
            w.x = 500;
            w.y = 500;

            nxi_core_.window_system().add(w);
        });
        /*
        sc = new QShortcut(QKeySequence("F1"), this);
        connect(sc, &QShortcut::activated, [this, tree]()
        {
            if (tree->isVisible()) tree->hide();
            else tree->show();
        });*/
    }

    main::~main()
    {}

    void main::keyPressEvent(QKeyEvent* event)
    {
        shortcut_->process(event);
    }

    void main::keyReleaseEvent(QKeyEvent* event)
    {
        shortcut_->process(event);
    }

    render::engine* main::engine()
    {
        return static_cast<render::engine*>(engine_web_);
    }
} // ui
