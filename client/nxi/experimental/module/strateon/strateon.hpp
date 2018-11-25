#ifndef EXP_MODULE_STRATEON_H_NXI
#define EXP_MODULE_STRATEON_H_NXI

#include <nxi/module.hpp>

namespace nxi { class core; }

namespace nxi::modules
{
    class strateon : public nxi::module
    {
    public:
        explicit strateon(nxi::core& nxi_core);

        void on_load();

    private:
        nxi::core& nxi_core_;

    };
} // nxi::modules

#endif // EXP_MODULE_STRATEON_H_NXI