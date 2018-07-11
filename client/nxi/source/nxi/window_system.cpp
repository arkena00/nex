#include <nxi/window_system.hpp>

#include <nxi/database/ui.hpp>

namespace nxi
{
    void window_system::add(nxi::window win)
    {
        m_windows.push_back(std::move(win));
        emit event_add(m_windows.back());
    }

    void window_system::position_set(ui::window*, int x, int y)
    {
        ndb::query<dbs::ui>() >> ()
    }
} // nxi