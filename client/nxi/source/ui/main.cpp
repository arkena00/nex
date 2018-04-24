#include <ui/window.hpp>
#include <ui/main.hpp>
#include <ui/tabwidget.hpp>
#include <ui/tabbar.hpp>
#include <ui/tab.hpp>
#include <ui/render/engine.hpp>
#include <ui/render/web.hpp>
#include <ui/render/nazara.hpp>

#include <nxs/network/connexion/output.hpp>

#include <QIcon>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <widget/bar.hpp>

namespace ui
{
    main::main(ui::window* window) :
        QWidget(window),
        _nxc(window->nxc())
    {
        // layouts
        QVBoxLayout* main_layout = new QVBoxLayout(this);
        QHBoxLayout* top_layout = new QHBoxLayout;
        QHBoxLayout* tool_layout = new QHBoxLayout;
        QHBoxLayout* middle_layout = new QHBoxLayout;
        QHBoxLayout* bot_layout = new QHBoxLayout;
        QVBoxLayout* left_layout = new QVBoxLayout;
        QVBoxLayout* right_layout = new QVBoxLayout;

        main_layout->addLayout(top_layout);
        main_layout->addLayout(tool_layout);
        main_layout->addLayout(middle_layout);
        main_layout->addLayout(bot_layout);
        main_layout->setContentsMargins(5, 5, 0, 0);

        // splitter
        QSplitter* splitter = new QSplitter(this);
        QWidget* left_side = new QWidget(this);
        QWidget* right_side = new QWidget(this);

        // splitter
        left_side->setLayout(left_layout);
        left_side->setMinimumWidth(150);
        left_layout->setMargin(0);
        right_layout->setMargin(0);
        right_side->setLayout(right_layout);
        splitter->addWidget(left_side);
        splitter->setStretchFactor(0, 0);
        splitter->addWidget(right_side);
        splitter->setStretchFactor(1, 1);
        middle_layout->addWidget(splitter);

         // menu button
        menu_button_ = new QPushButton(this);
        menu_button_->setObjectName("menu_button");
        menu_button_->setFixedSize(24, 24);
        menu_button_->setIcon(QIcon(":/image/menu"));
        menu_button_->setIconSize(QSize(16, 16));
        menu_button_->setCheckable(1);

        // new tab
        QPushButton* tab_new = new QPushButton(this);
        tab_new->setObjectName("tab_new");
        tab_new->setFixedSize(24, 24);
        tab_new->setIcon(QIcon(":/image/tab_new"));
        tab_new->setIconSize(QSize(16, 16));
        QObject::connect(tab_new, &QPushButton::clicked, [&]() { tabwidget_->add(); } );

        // tool bar
        tool_bar_ = new widget::bar(this);
        tool_bar_->setFixedHeight(24);
        tool_bar_->setContentsMargins(0, 0, 0, 0);

        tabwidget_ = new ui::tabwidget(this);
        tabwidget_->stack_add("status");
        tabwidget_->stack_add("address");
        tabwidget_->stack_add("tree");

        // status stack
        tool_bar_->add(tabwidget_->stack("status"));
        tabwidget_->stack("status")->setFixedSize(24, 24);

        // notification
        notification_button_ = new QPushButton(tool_bar_);
        notification_button_->setObjectName("notification_button");
        notification_button_->setIcon(QIcon(":/image/notification_status_0"));
        notification_button_->setIconSize(QSize(16, 16));
        tool_bar_->add(notification_button_);

        // address stack
        tool_bar_->add(tabwidget_->stack("address"));

        // engine
        engine_web_ = new ui::render::web(this);
        engine_web_->widget()->hide();
        //engine_nazara_ = new ui::render::nazara(this);


        // fill layouts
        top_layout->addWidget(menu_button_);
        top_layout->addWidget(&tabwidget_->tabbar());
        top_layout->addWidget(tab_new);
        top_layout->addStretch(1);
        tool_layout->addWidget(tool_bar_);
        left_layout->addWidget(tabwidget_->stack("tree"));
        //right_layout->addWidget(engine_web_->widget());
        //right_layout->addWidget(engine_nazara_->widget());

        // tab change
        QObject::connect(&tabwidget_->tabbar(), &QTabBar::currentChanged, [&](int index)
        {
            engine().load(&tabwidget_->tab(index).page());
        });

        // add tab
        tabwidget_->add();
    }

    main::~main()
    {
    }

    render::engine& main::engine()
    {
        return *engine_web_;
    }

    nxs::network::client& main::client()
    {
        return _nxc.client();
    }
} // ui
