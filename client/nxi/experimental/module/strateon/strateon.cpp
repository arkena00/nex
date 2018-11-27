#include "strateon.hpp"

#include <nxi/core.hpp>
#include <nxi/window.hpp>
#include <nxi/system/window.hpp>
#include <nxi/log.hpp>
#include <experimental/module/strateon/Core/MainWindow.h>


#include <nxi/page/custom.hpp>
#include <QtCore/qglobal.h>


namespace nxi::modules
{
    strateon::strateon(nxi::core& nxi_core)
        : module("strateon", module_type::compiled)
        , nxi_core_{ nxi_core }
    {}

    void strateon::on_load()
    {
        nxi_log << "load static module strateon";


        // custom_page
        QObject::connect(&nxi_core_.page_system(), qOverload<nxi::custom_page&, nxi::page_id>(&nxi::page_system::event_add), [this](nxi::custom_page& page, nxi::page_id source_id)
        {
            auto win = new MainWindow;
            win->show();
            nxi_core_.test(win);
            //page.name_update("document.txt");
        });


        auto action = [this]()
        {
            nxi_core_.page_system().add<custom_page>(0);
        };

        auto cmd = nxi::command("strateon", "main", action, ":/strateon/logo");



        nxi_core_.command_system().add(std::move(cmd));
    }

} // nxi::modules