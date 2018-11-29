#include <ui/core.hpp>

#include <nxi/core.hpp>
#include <nxi/database.hpp>
#include <nxi/log.hpp>

#include <ui/system/page.hpp>
#include <ui/system/window.hpp>

#include <QApplication>
#include <QFile>
#include <QSystemTrayIcon>
#include <QtWebEngine>

#include <ui/interface/home.hpp>
#include <ui/interface/page_bar.hpp>


namespace ui
{
    core::core(QApplication& app, nxi::core& nxi_core) :
        app_{ app }
        , nxi_core_{ nxi_core }
        , page_system_{ *this }
        , window_system_{ *this }
    {
        QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

        QtWebEngine::initialize();

        // load qss
        QFile qss_file(":/style.qss");
        qss_file.open(QFile::ReadOnly);
        QString qss = QLatin1String(qss_file.readAll());
        app_.setStyleSheet(qss);

        // systray
        systray_ = new QSystemTrayIcon;
        systray_->setIcon(QIcon(":/image/nex"));
        systray_->show();

        QObject::connect(&nxi_core_, &nxi::core::event_quit, this, &core::quit);
    }

    void core::quit()
    {
        window_system_.unload();

        QApplication::quit();
    }

    nxi::core& core::nxi_core()
    {
        return nxi_core_;
    }

    ui::page_system& core::page_system()
    {
        return page_system_;
    }

    ui::window_system& core::window_system()
    {
        return window_system_;
    }

    /*
    ui::page_system& core::page_system()
    {
        return m_page_system;
    }*/
} // ui