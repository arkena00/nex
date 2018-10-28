#include <nxi/system/window.hpp>

#include <nxi/core.hpp>
#include <nxi/database.hpp>
#include <nxi/log.hpp>

namespace nxi
{
	window_system::window_system(nxi::core& nxi_core) :
		nxi_core_{ nxi_core }
	{}

    void window_system::load()
    {
        nxi_log << "load window_system";

        // load stored windows
        auto res = ndb::query<dbs::core>() << (
        ndb::get(nxi_model.window.id, nxi_model.window.x, nxi_model.window.y, nxi_model.window.w, nxi_model.window.h)
        << ndb::source(nxi_model.window));
        for (auto& line : res)
        {
            nxi::window w;
            w.id = line[nxi_model.window.id];
            w.x = line[nxi_model.window.x];
            w.y = line[nxi_model.window.y];
            w.w = line[nxi_model.window.w];
            w.h = line[nxi_model.window.h];
            m_windows.push_back(w);
        }
    }

    void window_system::add(nxi::window win)
    {
        win.id = 1;
        ndb::query<dbs::core>() << ndb::add(
        nxi_model.window.x = win.x
        , nxi_model.window.y = win.y
        , nxi_model.window.w = win.w
        , nxi_model.window.h = win.h
        );

        m_windows.push_back(win);

        emit event_add((win));
    }

    void window_system::del(int id)
    {
        ndb::query<dbs::core>() << (ndb::del << ndb::source(nxi_model.window) << ndb::filter(nxi_model.window.id == id));
    }

    void window_system::move(unsigned int id, int x, int y)
    {
        ndb::query<dbs::core>() << ndb::set(nxi_model.window.x = x, nxi_model.window.y = y);
        emit event_position_update(x, y);
    }

    void window_system::resize(unsigned int id, int w, int h)
    {
        ndb::query<dbs::core>() << ndb::set(nxi_model.window.w = w, nxi_model.window.h = h);
    }

    std::vector<nxi::window>& window_system::get()
    {
        return m_windows;
    }
} // nxi