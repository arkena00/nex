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

    private:
        QString name_;
    };
} // nxi

#endif // NXI_MODULE_H_NXI