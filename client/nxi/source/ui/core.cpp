#include <ui/core.hpp>

#include <nxi/core.hpp>
#include <nxi/database/ui.hpp>
#include <nxi/log.hpp>

#include <QApplication>
#include <QFile>
#include <QSystemTrayIcon>
#include <QtWebEngine>

#include <ui/interface/home.hpp>
#include <ui/interface/page_bar.hpp>

namespace ui
{
    core::core(QApplication& app, nxi::core& nxi_core) :
        m_app{ app }
        , m_nxi_core{ nxi_core }
        , m_window_system{ *this }
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
        m_app.setStyleSheet(qss);

        // systray
        m_systray = new QSystemTrayIcon;
        m_systray->setIcon(QIcon(":/image/nex"));
        m_systray->show();

        m_window_system.load();
        //m_page_system.load();
    }

    void core::quit() const
    {
        QApplication::quit();
    }

    nxi::core& core::nxi_core()
    {
        return m_nxi_core;
    }

    ui::window_system& core::window_system()
    {
        return m_window_system;
    }

    /*
    ui::page_system& core::page_system()
    {
        return m_page_system;
    }*/
} // ui