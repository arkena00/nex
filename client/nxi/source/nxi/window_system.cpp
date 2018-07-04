#include <nxi/window_system.hpp>

namespace nxi
{
    void window_system::add(nxi::window win)
    {
        const auto& window = ndb::models::nxi_model.window;

        ndb::query<db_main>() + (window.x = win.x, window.y = win.y);
        win.id = ndb::last_id<db_main>();

        windows_.push_back(std::move(win));

        emit event_add(windows_.back());
    }

    void window_system::load()
    {
        const auto& window = ndb::models::nxi_model.window;

        for (auto& win : ndb::oquery<db_main>() << window)
        {
            windows_.push_back(win);
            emit event_add(win);
        }
    }

    const QVector<nxi::window>& window_system::windows() const
    {
        return windows_;
    }
} // nxi