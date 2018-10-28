#include "test.hpp"

#include <nxi/core.hpp>
#include <nxi/window.hpp>
#include <nxi/system/window.hpp>
#include <nxi/log.hpp>

namespace nxi::modules
{
    test::test(nxi::core& nxi_core) : nxi_core_{ nxi_core } {}

    void test::load()
    {
        nxi_log << "load test module";

        nxi::window tw;
        tw.x = 20;
        tw.y = 20;
        tw.w = 300;
        tw.h = 300;

        //nxi_core_.window_system().add(tw);
    }

} // nxi::modules