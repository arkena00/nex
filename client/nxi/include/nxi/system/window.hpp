#ifndef NXI_WINDOW_SYSTEM_H_NXI
#define NXI_WINDOW_SYSTEM_H_NXI

#include <nxi/window.hpp>

#include <QObject>

namespace nxi
{
	class core;

	enum class window_states { normal, minimized, maximized };

    class window_system : public QObject
    {
        Q_OBJECT
    public:
		window_system(nxi::core&);
        window_system(const window_system&) = delete;
        void operator=(const window_system&) = delete;

        void load();
        void add(nxi::window);
        void del(int id);
        std::map<unsigned int, nxi::window>& get();

        void move(unsigned int id, int x, int y);
        void resize(unsigned int id, int w, int h);
        void minimize(unsigned int id);

    signals:
        void event_add(const nxi::window&);
        void event_position_update(int x, int y);
        void event_state_update(unsigned int id, window_states state);

    private:
		nxi::core& nxi_core_;
        std::map<unsigned int, nxi::window> windows_;
        unsigned int m_current;
    };
} // nxi

#endif // NXI_WINDOW_SYSTEM_H_NXI