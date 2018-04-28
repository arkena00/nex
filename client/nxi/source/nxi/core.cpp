#include <nxi/core.hpp>
#include <nxs/network/client.hpp>

namespace nxi
{
    core::core() :
        client_thread_(&nxs::network::client::run, &client_)
    {}

    core::~core()
    {
        client_.stop();
        client_thread_.join();
    }

    nxs::network::client& core::client()
    {
        return client_;
    }

    nxi::tabsystem& core::tabsystem()
    {
        return tabsystem_;
    }
} // nxi
