#ifndef NXI_MODULE_H_NXI
#define NXI_MODULE_H_NXI

#include <nxi/database.hpp>

enum class module_type { web, binary };

class QString;

namespace nxi
{
    class module
    {
    public:
        module() {}

        virtual const QString& name() const = 0;
        virtual module_type type() const = 0;

    private:
        QString name_;
    };
} // nxi

#endif // NXI_MODULE_H_NXI