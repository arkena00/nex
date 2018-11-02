#ifndef NXI_MODULE_H_NXI
#define NXI_MODULE_H_NXI

#include <nxi/database.hpp>

class QString;

namespace nxi
{
    class module
    {
    public:
        module() {}
    };

    class binary_module : public module
    {
    public:
        binary_module(const QString& name) {}
    };


    class web_module : public module
    {
    public:
        web_module(const QString& name);

    private:

    };
} // nxi

#endif // NXI_MODULE_H_NXI