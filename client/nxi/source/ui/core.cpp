#include <ui/core.hpp>

#include <nxi/core.hpp>
#include <nxi/database.hpp>
#include <nxi/log.hpp>

#include <QApplication>
#include <QFile>
#include <QSystemTrayIcon>
#include <QtWebEngine>

#include <ui/interface/home.hpp>
#include <ui/interface/page_bar.hpp>
#include <include/ui/core.hpp>


namespace ui
{
    core::core(QApplication& app, nxi::core& nxi_core) :
        app_{ app }
        , nxi_core_{ nxi_core }
        , window_system_{ *this }
    {
        nxi_log << "init ui::core";

        QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

        QtWebEngine::initialize();
    }

    void core::load()
    {
        nxi_log << "load ui";

        // load qss
        QFile qss_file(":/style.qss");
        qss_file.open(QFile::ReadOnly);
        QString qss = QLatin1String(qss_file.readAll());
        app_.setStyleSheet(qss);

        // systray
        systray_ = new QSystemTrayIcon;
        systray_->setIcon(QIcon(":/image/nex"));
        systray_->show();

        window_system_.load();
        //m_page_system.load();
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