#include <nxi/core.hpp>

namespace nxi
{
    core::core() :
        client_thread_{ &nxs::network::client::run, &client_ }
    {
        try
        {
            //ndb::connect<db_main>();
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

    nxi::window_system& core::window_system()
    {
        return window_system_;
    }
} // nxi
