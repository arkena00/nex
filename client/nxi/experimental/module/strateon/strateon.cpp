#include "strateon.hpp"

#include <nxi/core.hpp>
#include <nxi/window.hpp>
#include <nxi/system/window.hpp>
#include <nxi/log.hpp>
#include <experimental/module/strateon/Core/MainWindow.h>

namespace nxi::modules
{
    strateon::strateon(nxi::core& nxi_core)
        : module("strateon", module_type::compiled)
        , nxi_core_{ nxi_core }
    {}

    void strateon::on_load()
    {
        nxi_log << "load static module strateon";

        auto action = []()
        {
            auto win = new MainWindow;
            win->show();
        };

        auto cmd = nxi::command("strateon", "main", action, ":/strateon/logo");




        nxi_core_.command_system().add(cmd);
    }

} // nxi::modules