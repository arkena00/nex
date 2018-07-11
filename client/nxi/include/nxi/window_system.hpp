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

        void position_set(ui::window*, int x, int y);

    signals:
        void event_add(nxi::window&);

    private:
        QVector<nxi::window> m_windows;
    };
} // nxi

#endif // NXI_WINDOW_SYSTEM_H_NXI