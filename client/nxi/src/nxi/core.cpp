#include <nxi/core.hpp>
#include <nxs/network/client.hpp>

namespace nxi
{
    core::core()
    {
        // create nxs::client to manage output connexions
        std::thread client_thread(&nxs::network::client::run, &_client);
        client_thread.detach();
    }

    nxs::network::client& core::client() { return _client; }
} // nxi
