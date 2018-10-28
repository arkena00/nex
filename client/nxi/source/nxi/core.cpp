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
    {
        nxi_log << "init core";
        try
        {
            ndb::connect<dbs::core>();

            window_system_.load();
            page_system_.load();

            module_system_.load();
        }
        catch (const std::exception& e)
        {
            client_.stop();
            client_thread_.join();
            throw;
        }
    }

    core::~core()
    {
        client_.stop();
        client_thread_.join();
    }

    nxi::command_system& core::command_system()
    {
        return command_system_;
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
