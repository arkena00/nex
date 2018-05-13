#include <ui/core.hpp>

#include <ui/main.hpp>
#include <ui/login.hpp>

#include <nxi/core.hpp>
#include <nxi/window_system.hpp>

#include <QApplication>
#include <QFile>
#include <QSystemTrayIcon>
#include <QtWebEngine>




namespace ui
{
    core::core(QApplication& app, nxi::core& nxi_core) :
        nxi_core_{ nxi_core }
    {
        // init webengine
        QtWebEngine::initialize();

        // load qss
        QFile qss_file(":/style.qss");
        qss_file.open(QFile::ReadOnly);
        QString qss = QLatin1String(qss_file.readAll());
        app.setStyleSheet(qss);

        // systray
        systray_ = new QSystemTrayIcon;
        systray_->setIcon(QIcon(":/image/nex"));
        systray_->show();

        // load window
        //TODO: webengine crash when window not deleted before exit


        QObject::connect(&nxi_core_.window_system(), &nxi::window_system::event_add, [this](nxi::window& w)
        {
            auto window = new ui::window(nxi_core_);
            window->load<ui::main>();
            window->move(w.x, w.y);
            window->show();
        });



        nxi_core_.window_system().load();
    }

    core::~core()
    {
       // delete window2_;
    }
} // ui