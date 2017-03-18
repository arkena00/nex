#include <QApplication>
#include "ui.hpp"

#include <nxs/core.hpp>
#include <nxs/network/client.hpp>
#include <nxs/network/connexion/output.hpp>

#include <NDK/Sdk.hpp>
#include <Nazara/Core/Initializer.hpp>

#include <nxi/core.hpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Nz::Initializer<Ndk::Sdk> n;

    nxi::core nxc;

    nxs::load();
    ui::load(app, nxc);

    app.exec();

    return 0;
}
