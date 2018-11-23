#ifndef NXI_MODULE_BINARY_H_NXI
#define NXI_MODULE_BINARY_H_NXI

#include <nxi/database.hpp>
#include <nxi/module.hpp>
#include <nxi/type.hpp>

namespace nxi
{
    class core;

    class dynamic_module : public module
    {
    public:
        dynamic_module(nxi::core&, const QString& name) : module(name, module_type::dynamic) {}

    };
} // nxi

#endif // NXI_MODULE_BINARY_H_NXI