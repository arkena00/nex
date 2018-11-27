#include "test.hpp"

#include <nxi/core.hpp>
#include <nxi/window.hpp>
#include <nxi/system/window.hpp>
#include <nxi/log.hpp>

namespace nxi::modules
{
    test::test(nxi::core& nxi_core)
        : module("static_module_test", module_type::compiled)
        , nxi_core_{ nxi_core }
    {}

    void test::on_load()
    {
        nxi_log << "load static test module";

        auto cmd = nxi::command("static_module_test", "action", std::bind(&nxi::core::quit, &nxi_core_));


        nxi_core_.command_system().add(std::move(cmd));
    }

} // nxi::modules