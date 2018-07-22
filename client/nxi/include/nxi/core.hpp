#ifndef CORE_H_NXI
#define CORE_H_NXI

#include <nxs/network/client.hpp>

#include <nxi/system/window.hpp>
#include <nxi/system/page.hpp>

namespace nxi
{
    class core
    {
    public:
        core();
        ~core();
        core(const core&) = delete;
        void operator=(const core&) = delete;

        nxi::window_system& window_system();
        nxi::page_system& page_system();

    private:
        ndb::initializer<ndb::sqlite> m_ndb_init;
        nxs::network::client m_client;
        std::thread m_client_thread;

        nxi::window_system m_window_system;
        nxi::page_system m_page_system;
    };
} // nxi

#endif // CORE_H_NXI