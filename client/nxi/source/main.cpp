#include <QApplication>
#include <nxi/core.hpp>
#include <ui/core.hpp>

int main(int argc, char* argv[])
{
    int status = 0;

    try
    {
        QApplication app(argc, argv);
        QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

        nxi::core nxi_core;
        ui::core ui_core(app, nxi_core);

        status = QApplication::exec();
    }
    catch (const std::exception& e)
    {
        //std::cout << e.what();
    }


    return status;
}
