#include <ui/core.hpp>

#include <ui/main.hpp>
#include <ui/login.hpp>

#include <nxi/core.hpp>

#include <QApplication>
#include <QSystemTrayIcon>
#include <QtWebEngine>

namespace ui
{
    core::core(QApplication& app, nxi::core& nxi_core) :
        nxi_core_{ nxi_core }
    {
        QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
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


        QObject::connect(&nxi_core_.window_system(), &nxi::window_system::event_add, [this](nxi::window& window)
        {
            ui::window::make(*this, window);
        });

        nxi_core_.window_system().load();
    }

    core::~core()
    {}
} // ui