#include <nxi/core.hpp>

#include <nxi/database/ui.hpp>
#include <nxi/log.hpp>

namespace nxi
{
    core::core() :
        m_client_thread{ &nxs::network::client::run, &m_client }
		, m_window_system{ *this }
    {
        nxi_log << "init core";
        try
        {
            ndb::connect<dbs::ui>();

            m_window_system.load();
            m_page_system.load();
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

    nxi::page_system& core::page_system()
    {
        return m_page_system;
    }
} // nxi
