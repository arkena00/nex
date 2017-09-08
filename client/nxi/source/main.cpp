#include <QApplication>
#include <nxs/core.hpp>
#include <nxi/core.hpp>
#include <ui/core.hpp>

int main(int argc, char* argv[])
{
    int status = 0;

    try
    {
        nxs::load();
        nxi::core nxc;

        QApplication app(argc, argv);

        ui::core uic(app, nxc);

        status = app.exec();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }


    return status;
}
