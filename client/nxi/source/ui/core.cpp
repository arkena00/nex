#include <ui/core.hpp>

#include <nxi/core.hpp>
#include <nxi/database/ui.hpp>

#include <QApplication>
#include <QFile>
#include <QSystemTrayIcon>
#include <QtWebEngine>

#include <ui/interface/home.hpp>
#include <ui/interface/page_bar.hpp>
#include <include/nxw/web_view.hpp>
#include <include/nxw/tree.hpp>
#include <include/ui/core.hpp>


namespace ui
{
    core::core(QApplication& app, nxi::core& nxi_core) :
        m_nxi_core{ nxi_core }
        , m_window_system{ *this }
    {
        QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

        QtWebEngine::initialize();

        // load qss
        QFile qss_file(":/style.qss");
        qss_file.open(QFile::ReadOnly);
        QString qss = QLatin1String(qss_file.readAll());
        app.setStyleSheet(qss);

        // systray
        m_systray = new QSystemTrayIcon;
        m_systray->setIcon(QIcon(":/image/nex"));
        m_systray->show();
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
} // ui