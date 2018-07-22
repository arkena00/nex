#ifndef NXI_WINDOW_SYSTEM_H_NXI
#define NXI_WINDOW_SYSTEM_H_NXI

#include <ui/window.hpp>

#include <QObject>

namespace nxi
{
    class window_system : public QObject
    {
        Q_OBJECT
    public:
        void add(nxi::window);

        void position_set(unsigned int m_id, int x, int y);

    signals:
        void event_add(const nxi::window&);
        void event_position_update(int x, int y);

    private:
        QHash<unsigned int, ui::window*> m_windows;
        unsigned int m_current;
    };
} // nxi

#endif // NXI_WINDOW_SYSTEM_H_NXI