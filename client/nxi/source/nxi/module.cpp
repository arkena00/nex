#include <nxi/module.hpp>

namespace nxi
{
    module::module(QString name, module_type type)
        : name_{ std::move(name) }
        , type_{ type }
        , loaded_{ false }
    {}

    void module::load()
    {
        on_load();
        loaded_ = true;
    }

    void module::unload()
    {
        on_unload();
        loaded_ = false;
    }

    void module::on_load() {}
    void module::on_unload() {}

    const QString& module::name() const
    {
        return name_;
    }

    module_type module::type() const
    {
        return type_;
    }

    bool module::is_loaded() const
    {
        return loaded_;
    }
} // nxi