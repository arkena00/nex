#include <nxi/system/window.hpp>

#include <nxi/core.hpp>
#include <nxi/database.hpp>
#include <nxi/log.hpp>
#include <include/nxi/system/window.hpp>


namespace nxi
{
	window_system::window_system(nxi::core& nxi_core) :
		nxi_core_{ nxi_core }
	{
        nxi_log << "init window_system";
	}

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
            windows_.emplace(w.id, std::move(w));
            emit event_add((w));
        }
    }

    void window_system::add(nxi::window win)
    {
        win.id = 0;
        ndb::query<dbs::core>() << ndb::add(
        nxi_model.window.x = win.x
        , nxi_model.window.y = win.y
        , nxi_model.window.w = win.w
        , nxi_model.window.h = win.h
        );

        win.id = ndb::last_id<dbs::core>();

        windows_.emplace(win.id, std::move(win));

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

    std::map<unsigned int, nxi::window>& window_system::get()
    {
        return windows_;
    }

    void window_system::minimize(unsigned int id)
    {
	    // windows_[id].state = window_states::minimized;
        emit event_state_update(id, window_states::minimized);
    }
} // nxi