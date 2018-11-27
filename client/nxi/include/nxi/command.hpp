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
		command(const QString& module_name, const QString& action_name, std::function<void()> fn, const QString& icon = ":/image/nex");
        command(command&&) = default;
        command& operator=(command&&) = default;

        command(const command&) = delete;
        command& operator=(const command&) = delete;

		void exec() const;

        const QString& name() const;
        const QString& module_name() const;
        const QString& action_name() const;
        const QString& icon() const;
        const std::function<void()>& function() const;

	private:
		QString module_name_;
		QString action_name_;
		QString name_;
		std::function<void()> function_;

        QString icon_;
        QString description_;
        // shortcut

		/*
		enum class interface_location{ none, page_bar, control_bar, content, custom };

		url_pattern{"http://*.com"};

		location
		matches

		webext : [](){ nxi_core.page_system().load(nxi::popup_page{path}) }
		 */
	};

    class web_module_command : public nxi::command
    {
	    //void exec()
    };

} // nxi

#endif // NXI_COMMAND_H_NXI