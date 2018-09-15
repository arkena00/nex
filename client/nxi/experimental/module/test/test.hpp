#ifndef EXP_MODULE_TEST_H_NXI
#define EXP_MODULE_TEST_H_NXI

#include <nxi/core.hpp>
#include <nxi/window.hpp>
#include <nxi/system/window.hpp>
#include <nxi/log.hpp>

namespace nxi_module
{
    class test
    {
    public:
        explicit test(nxi::core& nxi_core);

        void load();


    private:
        nxi::core& m_nxi_core;

    };
} // nxi

#endif // EXP_MODULE_TEST_H_NXI