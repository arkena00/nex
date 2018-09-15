#include <nxi/core.hpp>

#include <nxi/database.hpp>
#include <nxi/log.hpp>

namespace nxi
{
    core::core() :
        m_client_thread{ &nxs::network::client::run, &m_client }
        , m_command_system{ *this }
        , m_window_system{ *this }
        , m_module_system{ *this }
    {
        nxi_log << "init core";
        try
        {
            ndb::connect<dbs::core>();

            m_window_system.load();
            m_page_system.load();

            m_module_system.load();
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

    nxi::command_system& core::command_system()
    {
        return m_command_system;
    }

    nxi::page_system& core::page_system()
    {
        return m_page_system;
    }

    nxi::window_system& core::window_system()
    {
        return m_window_system;
    }
} // nxi
