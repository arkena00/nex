#include <ui/window.hpp>
#include <ui/main.hpp>
#include <ui/tabwidget.hpp>
#include <ui/tabbar.hpp>
#include <ui/render/web.hpp>
#include <ui/tree.hpp>

#include <nxs/network/connexion/output.hpp>

#include <QDebug>
#include <QIcon>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <nxi/error.hpp>

namespace ui
{
    main::main(ui::window* window) :
        QWidget(window),
        _nxc(window->nxc())
    {
        // layouts
        QVBoxLayout* main_layout = new QVBoxLayout(this);
        QHBoxLayout* top_layout = new QHBoxLayout;
        QHBoxLayout* top2_layout = new QHBoxLayout;
        QHBoxLayout* middle_layout = new QHBoxLayout;
        QHBoxLayout* bot_layout = new QHBoxLayout;
        QVBoxLayout* left_layout = new QVBoxLayout;
        QVBoxLayout* right_layout = new QVBoxLayout;

        main_layout->addLayout(top_layout);
        main_layout->addLayout(top2_layout);
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

        //// top
        // menu button
        menu_button_ = new QPushButton(this);
        menu_button_->setObjectName("menu_button");
        menu_button_->setFixedSize(24, 24);
        menu_button_->setIcon(QIcon(":/image/menu"));
        menu_button_->setIconSize(QSize(16, 16));
        menu_button_->setCheckable(1);
        top_layout->addWidget(menu_button_);

        // tabwidget
        tabwidget_ = new tabwidget(this);
        tabwidget_->stack_add("address");
        tabwidget_->stack_add("tree");
        left_layout->addWidget(tabwidget_->stack("tree"));

        // top
        top_layout->addWidget(tabwidget_->tabbar());

        // new tab
        QPushButton* tab_new = new QPushButton(this);
        tab_new->setObjectName("tab_new");
        tab_new->setFixedSize(24, 24);
        tab_new->setIcon(QIcon(":/image/tab_new"));
        tab_new->setIconSize(QSize(16, 16));
        top_layout->addWidget(tab_new);
        top_layout->addStretch(1);
        QObject::connect(tab_new, &QPushButton::clicked, [&]() { tabwidget_->add(); } );

        tabwidget_->stack("address")->setFixedHeight(24);
        top2_layout->addWidget(tabwidget_->stack("address"));

        tabwidget_->add();

        /*
        // engine stack
        engine_stack_ = new QStackedWidget(this);
        right_layout->addWidget(engine_stack_);

        auto engine = new render::web(this);
        engine_stack_->addWidget(engine->widget());

        // add tab
        tabwidget_->add();*/
    }

    main::~main()
    {
    }

    void main::tab_add(QString name)
    {

    }

    nxs::network::client& main::client() { return _nxc.client(); }
} // ui
