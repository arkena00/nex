#ifndef NXI_COMMAND_SYSTEM_H_NXI
#define NXI_COMMAND_SYSTEM_H_NXI

#include <nxi/window.hpp>

#include <QObject>

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
        void exec(const QString& command, command_context context = command_context::deduced);

    private:
		nxi::core& nxi_core_;
    };
} // nxi

#endif // NXI_COMMAND_SYSTEM_H_NXI