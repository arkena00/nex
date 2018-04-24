#include <nxi/core.hpp>
#include <nxs/network/client.hpp>

namespace nxi
{
    core::core() :
        m_client_thread(&nxs::network::client::run, &m_client)
    {}

    core::~core()
    {
        m_client.stop();
        m_client_thread.join();
    }

    nxs::network::client &core::client()
    {
        return m_client;
    }
} // nxi
