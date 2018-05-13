#include <nxi/core.hpp>

#include <nxi/database.hpp>

#include <nxs/network/client.hpp>

namespace nxi
{
    core::core() :
        client_thread_{ &nxs::network::client::run, &client_ }
    {
        ndb::connect<db_main>();
    }

    core::~core()
    {
        client_.stop();
        client_thread_.join();
    }

    nxs::network::client& core::client()
    {
        return client_;
    }

    nxi::window_system& core::window_system()
    {
        return window_system_;
    }

    nxi::tabsystem& core::tabsystem()
    {
        return tabsystem_;
    }
} // nxi
