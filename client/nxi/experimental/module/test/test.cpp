#include "test.hpp"

namespace nxi_module
{
    test::test(nxi::core& nxi_core) : m_nxi_core{ nxi_core } {}

    void test::load()
    {
        nxi_log << "load test module";

        nxi::window tw;
        tw.x = 20;
        tw.y = 20;
        tw.w = 300;
        tw.h = 300;

        m_nxi_core.window_system().add(tw);
    }

} // nxi