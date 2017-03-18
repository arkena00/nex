#include "ui.hpp"
#include "ui/main.hpp"

#include <QApplication>
#include <QWindow>
#include <QFile>

namespace ui
{
    void load(QApplication& app, nxi::core& nxc)
    {
        // load qss
        QFile qss_file(":/style.qss");
        qss_file.open(QFile::ReadOnly);
        QString qss = QLatin1String(qss_file.readAll());
        app.setStyleSheet(qss);

        // create main window
        auto win = new ui::main(nxc);
        win->show();
    }
} // ui
