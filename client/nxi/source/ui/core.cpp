#include <ui/core.hpp>
#include <QApplication>
#include <QFile>

namespace ui
{
    core::core(QApplication& app, nxi::core& nxc) :
        window_(nxc)
    {
        // load qss
        QFile qss_file(":/style.qss");
        qss_file.open(QFile::ReadOnly);
        QString qss = QLatin1String(qss_file.readAll());
        app.setStyleSheet(qss);

        window_.show();
    }
} // ui