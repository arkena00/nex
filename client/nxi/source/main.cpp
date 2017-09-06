#include <QApplication>
#include <nxs/core.hpp>
#include <nxi/core.hpp>
#include <ui/core.hpp>

int main(int argc, char* argv[])
{
    int status = 0;

    try
    {
        QApplication app(argc, argv);

        nxs::load();
        nxi::core nxc;
        ui::core uic(app, nxc);

        status = app.exec();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }


    return status;
}
