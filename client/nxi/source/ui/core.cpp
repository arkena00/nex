#include <ui/core.hpp>

#include <nxi/core.hpp>
#include <nxi/database/ui.hpp>

#include <QApplication>
#include <QFile>
#include <QSystemTrayIcon>
#include <QtWebEngine>

namespace ui
{
    core::core(QApplication& app, nxi::core& nxi_core) :
        m_nxi_core{ nxi_core }
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
        m_systray = new QSystemTrayIcon;
        m_systray->setIcon(QIcon(":/image/nex"));
        m_systray->show();


        QObject::connect(&m_nxi_core.window_system(), &nxi::window_system::event_add, [this](nxi::window& window)
        {
            ui::window::make(*this, window);
        });

        nxi::window win;
        win.x = 200;
        win.y = 200;
        m_nxi_core.window_system().add(std::move(win));
    }

    core::~core()
    {}

    nxi::core& core::nxi_core()
    {
        return m_nxi_core;
    }
} // ui