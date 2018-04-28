#include <ui/core.hpp>

#include <QApplication>
#include <QFile>
#include <QSystemTrayIcon>
#include <QtWebEngine>
#include <include/ui/login.hpp>

#include <ui/main.hpp>

namespace ui
{
    core::core(QApplication& app, nxi::core& nxi_core) :
        window_{ nxi_core }
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
        window_.load<ui::login>();
        window_.show();

        auto win2 = new ui::window(nxi_core);
        win2->load<ui::main>();
        win2->move(-1600, 200);
        win2->show();
    }
} // ui