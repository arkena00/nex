#ifndef NXI_COMMAND_SYSTEM_H_NXI
#define NXI_COMMAND_SYSTEM_H_NXI

#include <nxi/window.hpp>

#include <QObject>

namespace nxi
{
	class core;

    class command_system : public QObject
    {
        Q_OBJECT
    public:
		command_system(nxi::core&);
		command_system(const command_system&) = delete;
        void operator=(const command_system&) = delete;

        void load();
        void exec(const QString& command);

    private:
		nxi::core& m_nxi_core;
    };
} // nxi

#endif // NXI_COMMAND_SYSTEM_H_NXI