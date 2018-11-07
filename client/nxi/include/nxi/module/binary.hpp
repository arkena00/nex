#ifndef NXI_MODULE_BINARY_H_NXI
#define NXI_MODULE_BINARY_H_NXI

#include <nxi/database.hpp>
#include <nxi/module.hpp>

namespace nxi
{
    class binary_module : public module
    {
    public:
        binary_module(const QString& name) {}

        const QString& name() const override { return "binary"; }

        module_type type() const override { return module_type::binary; }
    };
} // nxi

#endif // NXI_MODULE_H_NXI