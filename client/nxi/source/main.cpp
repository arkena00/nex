#include <QApplication>
#include <QMessageBox>

#include <nxi/core.hpp>
#include <ui/core.hpp>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QMessageBox error;
    int status = 0;

    try
    {
        nxi::core nxi_core;
        ui::core ui_core(app, nxi_core);

        status = QApplication::exec();
    }
    catch (const std::exception& e)
    {
        error.setText(e.what());
        error.show();
        status = QApplication::exec();
    }

    return status;
}
