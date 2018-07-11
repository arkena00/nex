#include <nxi/core.hpp>

#include <nxi/database/ui.hpp>

namespace nxi
{
    core::core() :
        m_client_thread{ &nxs::network::client::run, &m_client }
    {
        try
        {
            ndb::connect<dbs::ui>();
        }
        catch (const std::exception& e)
        {
            m_client.stop();
            m_client_thread.join();
            throw;
        }
    }

    core::~core()
    {
        m_client.stop();
        m_client_thread.join();
    }

    nxi::window_system& core::window_system()
    {
        return m_window_system;
    }
} // nxi
