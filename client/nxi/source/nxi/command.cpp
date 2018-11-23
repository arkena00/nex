#include <nxi/command.hpp>

namespace nxi
{
    command::command(const QString& module_name, const QString& action_name, std::function<void()> fn, const QString& icon)
        : module_name_{ module_name }
        , action_name_{ action_name }
        , name_{ module_name_ + ":" + action_name_ }
        , icon_{ icon }
        , function_{ std::move(fn) }
    {}

    void command::exec() const
    {
        if (function_) function_();
    }

    const QString& command::name() const
    {
        return name_;
    }

    const QString& command::module_name() const
    {
        return module_name_;
    }

    const QString& command::action_name() const
    {
        return action_name_;
    }

    const QString& command::icon() const
    {
        return icon_;
    }

    const std::function<void()>& command::function() const
    {
        return function_;
    }
} // nxi