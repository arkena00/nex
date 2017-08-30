#include "ui/main.hpp"
#include "ui/tab.hpp"
#include "ui/tabbar.hpp"

#include <nxs/network/connexion/output.hpp>

#include <QDebug>
#include <QIcon>
#include <QDesktopWidget>
#include <QVBoxLayout>

namespace ui
{
    main::main(nxi::core& nxc) : _nxc(nxc)
    {
        QIcon icon(":image/nex");
        setWindowIcon(icon);

        // main window
        QDesktopWidget screen;
        QRect screen_size = screen.availableGeometry(screen.primaryScreen());
        size_t width = screen_size.width() * 0.8;
        size_t height = screen_size.height() * 0.7;
        size_t x = (screen_size.width() - width) / 2;
        size_t y = (screen_size.height() - height) / 2;
        // center window
        resize(width, height);
        move(x, y);
        setWindowTitle("nxi");

        QVBoxLayout* main_layout = new QVBoxLayout(this);
        QHBoxLayout* top_layout = new QHBoxLayout;

        main_layout->addLayout(top_layout);
        main_layout->setContentsMargins(5, 5, 0, 0);

        // tabstack
        _tabstack = new QStackedWidget(this);
        main_layout->addWidget(_tabstack);

        //// top
        // menu button
        _menu_button = new QPushButton(this);
        _menu_button->setObjectName("menu_button");
        _menu_button->setFixedSize(24, 24);
        _menu_button->setIcon(QIcon(":/image/menu"));
        _menu_button->setIconSize(QSize(16, 16));
        _menu_button->setCheckable(1);
        top_layout->addWidget(_menu_button);

        // tabbar
        _tabbar = new ui::tabbar(this);
        _tabbar->setObjectName("tab");
        _tabbar->setTabsClosable(1);
        _tabbar->setMovable(1);
        _tabbar->setDrawBase(0);
        top_layout->addWidget(_tabbar);
        QObject::connect(_tabbar, &QTabBar::tabBarClicked, [&](int index) { _tabstack->setCurrentIndex(index); });
        QObject::connect(_tabbar, &QTabBar::tabCloseRequested, this, &main::tab_close);

        // new tab
        QPushButton* tab_new = new QPushButton(this);
        tab_new->setObjectName("tab_new");
        tab_new->setFixedSize(24, 24);
        tab_new->setIcon(QIcon(":/image/tab_new"));
        tab_new->setIconSize(QSize(16, 16));
        top_layout->addWidget(tab_new);
        top_layout->addStretch(1);
        QObject::connect(tab_new, &QPushButton::clicked, this,  &main::tab_add_click);

        // systray
        _systray = new QSystemTrayIcon(this);
        //_systray->setIcon(QIcon(":/image/nex"));
        //_systray->show();

        // add tab
        tab_add();
    }

    main::~main()
    {
    }

    void main::tab_add_click()
    {
        tab_add();
    }

    void main::tab_close(int index)
    {
        if (_tabbar->count() == 1) return;
        _tabbar->removeTab(index);
        delete _tabstack->widget(index);
    }


    void main::tab_add(QString name)
    {
        // new tab index
        size_t index = _tabbar->count();

        // create tab
        _tabbar->addTab(name);

        // create tab widget
        ui::tab* tab = new ui::tab(this, index);
        _tabstack->addWidget(tab);

        // change index
        _tabbar->setCurrentIndex(index);
        _tabstack->setCurrentIndex(index);

        _tabbar->setTabText(index, name);
    }

    nxs::network::client& main::client() { return _nxc.client(); }

    ui::tabbar& main::tabbar() { return *_tabbar; }

} // ui
