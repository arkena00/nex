#ifndef NXI_COMMAND_H_NXI
#define NXI_COMMAND_H_NXI

#include <nxi/window.hpp>

#include <functional>
#include <QObject>
#include <QHash>
#include <QDebug>

namespace nxi
{
	class core;

	class command
	{
	public:
		command(const QString& module_name, const QString& action_name, std::function<void()> fn, const QString& icon = ":/image/nex")
		    : module_name_{ module_name }
		    , action_name_{ action_name }
		    , command_name_{ module_name_ + ":" + action_name_ }
		    , icon_{ icon }
		    , function_{ std::move(fn) }
		{
		}

		void exec() const
        {
	        if (function_) function_();
        }

        const QString& command_name() const
        {
            return command_name_;
        }

        const QString& module_name() const
        {
            return module_name_;
        }

        const QString& action_name() const
        {
            return action_name_;
        }

        const QString& icon() const
        {
            return icon_;
        }

        const std::function<void()>& function() const
        {
            return function_;
        }

	private:
		QString module_name_;
		QString action_name_;
		QString command_name_;
		QString icon_;
		std::function<void()> function_;
	};

} // nxi

#endif // NXI_COMMAND_H_NXI