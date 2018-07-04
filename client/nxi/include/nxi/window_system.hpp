#ifndef NXI_WINDOW_SYSTEM_H_NXI
#define NXI_WINDOW_SYSTEM_H_NXI

#include <nxi/database.hpp>

#include <QObject>
#include <QVector>

namespace nxi
{
    using window = ndb::objects::window;

    class window_system : public QObject
    {
        Q_OBJECT
    public:
        void add(nxi::window);
        void load();

        const QVector<nxi::window>& windows() const;

    signals:
        void event_add(nxi::window&);
        void event_change();

    private:
        QVector<nxi::window> windows_;
    };
} // nxi

#endif // NXI_WINDOW_SYSTEM_H_NXI