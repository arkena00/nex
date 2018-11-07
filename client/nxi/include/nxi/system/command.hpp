#ifndef NXI_COMMAND_SYSTEM_H_NXI
#define NXI_COMMAND_SYSTEM_H_NXI

#include <nxi/command.hpp>
#include <nxi/window.hpp>

#include <functional>
#include <QObject>
#include <QHash>

namespace nxi
{
	class core;

	enum class command_context { deduced, web, explorer };

    class command_system : public QObject
    {
        Q_OBJECT
    public:
		command_system(nxi::core&);
		command_system(const command_system&) = delete;
        void operator=(const command_system&) = delete;

        void load();

        const std::vector<nxi::command>& get();
        const nxi::command& get(const QString& module_action, const QString& module_name = "nxi") const;
		void add(nxi::command command);
        void exec(const QString& command, command_context context = command_context::deduced);

        signals:
        void event_add(const nxi::command&);

    private:
		nxi::core& nxi_core_;

		std::vector<nxi::command> commands_;
		QHash<QString, size_t> command_indexes_;
		//QHash<shortcut, unsigned int
    };
} // nxi

#endif // NXI_COMMAND_SYSTEM_H_NXI