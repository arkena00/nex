#ifndef NXI_WINDOW_SYSTEM_H_NXI
#define NXI_WINDOW_SYSTEM_H_NXI

#include <nxi/window.hpp>

#include <QObject>

namespace nxi
{
	class core;

    class window_system : public QObject
    {
        Q_OBJECT
    public:
		window_system(nxi::core&);
        window_system(const window_system&) = delete;
        void operator=(const window_system&) = delete;

        void load();
        void add(nxi::window);
        std::vector<nxi::window>& get();

        void position_set(unsigned int m_id, int x, int y);

    signals:
        void event_add(const nxi::window&);
        void event_position_update(int x, int y);

    private:
		nxi::core& m_nxi_core;
        std::vector<nxi::window> m_windows;
        unsigned int m_current;
    };
} // nxi

#endif // NXI_WINDOW_SYSTEM_H_NXI