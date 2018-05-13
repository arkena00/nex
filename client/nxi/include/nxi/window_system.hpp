#ifndef NXI_WINDOWSYSTEM_H_NXI
#define NXI_WINDOWSYSTEM_H_NXI

#include <ndb/query.hpp>
#include <nxi/database.hpp>

#include <QObject>
#include <QVector>
#include <include/ui/window.hpp>

namespace nxi
{
    struct window
    {
        int id;
        int x = 200;
        int y = 200;

    };

    class window_system : public QObject
    {
        Q_OBJECT
    public:
        void add()
        {
            nxi::window w;
            windows_.push_back(w);

            const auto& win = ndb::models::nxi_model.window;

            ndb::query<db_main>() + (win.x = w.x, win.y = w.y);

            emit event_add(windows_.back());
        }

        void load()
        {
            const auto& win = ndb::models::nxi_model.window;

            auto result = ndb::query<db_main>() << win;


            for (const auto& line : result)
            {
                nxi::window w;
                w.x = line[win.x];
                w.y = line[win.y];
                emit event_add(w);
            }
        }

        void change()
        {

        }

    signals:
        void event_add(nxi::window&);
        void event_change();

    private:
        QVector<nxi::window> windows_;
    };
} // nxi

#endif // NXI_WINDOWSYSTEM_H_NXI