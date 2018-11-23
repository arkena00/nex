#include <nxi/core.hpp>

#include <nxi/database.hpp>
#include <nxi/log.hpp>

namespace nxi
{
    core::core() :
        client_thread_{ &nxs::network::client::run, &client_ }
        , command_system_{ *this }
        , window_system_{ *this }
        , module_system_{ *this }
    {}

    core::~core()
    {
        client_.stop();
        client_thread_.join();
    }

    void core::load()
    {
        // load modules before other systems
        module_system_.load();

        command_system_.load();
        window_system_.load();
        page_system_.load();
    }

    void core::quit() const
    {
        emit event_quit();
    }

    nxi::command_system& core::command_system()
    {
        return command_system_;
    }

    nxi::module_system& core::module_system()
    {
        return module_system_;
    }

    nxi::page_system& core::page_system()
    {
        return page_system_;
    }

    nxi::window_system& core::window_system()
    {
        return window_system_;
    }
} // nxi
