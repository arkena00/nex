#include <QApplication>
#include "ui.hpp"
#include <nxs/core.hpp>
#include <nxs/network/client.hpp>
#include <QDebug>

#include <nxi/core.hpp>

using namespace nxs::network;

int main(int argc, char *argv[])
{
    try
    {
        nxs::load();
    } catch (const std::exception& e)
    {
        std::cout << "ERROR : " << e.what();
        return EXIT_FAILURE;
    }

    QApplication app(argc, argv);

    nxi::core nxc;
    ui::load(app, nxc);


    return app.exec();
}
