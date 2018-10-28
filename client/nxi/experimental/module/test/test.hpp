#ifndef EXP_MODULE_TEST_H_NXI
#define EXP_MODULE_TEST_H_NXI

namespace nxi { class core; }

namespace nxi::modules
{
    class test
    {
    public:
        explicit test(nxi::core& nxi_core);

        void load();


    private:
        nxi::core& nxi_core_;

    };
} // nxi::modules

#endif // EXP_MODULE_TEST_H_NXI