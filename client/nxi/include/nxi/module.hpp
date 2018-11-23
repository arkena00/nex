#ifndef NXI_MODULE_H_NXI
#define NXI_MODULE_H_NXI

#include <nxi/database.hpp>
#include <nxi/type.hpp>

class QString;

namespace nxi
{
    class module
    {
    public:
        module(QString name, module_type);

        void load();
        void unload();

        virtual void on_load();
        virtual void on_unload();

        const QString& name() const;
        module_type type() const;
        bool is_loaded() const;

    private:
        QString name_;
        module_type type_;
        bool loaded_;
    };
} // nxi

#endif // NXI_MODULE_H_NXI