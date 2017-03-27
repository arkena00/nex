#include <QApplication>
#include <nxs/core.hpp>
#include <nxi/core.hpp>
#include <ui/core.hpp>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    nxs::load();
    nxi::core nxc;
    ui::core uic(app, nxc);

    return app.exec();
}
