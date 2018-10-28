#ifndef CORE_H_NXI
#define CORE_H_NXI

#include <nxs/network/client.hpp>

#include <nxi/system/command.hpp>
#include <nxi/system/page.hpp>
#include <nxi/system/module.hpp>
#include <nxi/system/window.hpp>

namespace nxi
{
    class core
    {
    public:
        core();
        ~core();
        core(const core&) = delete;
        void operator=(const core&) = delete;

        nxi::command_system& command_system();
        nxi::page_system& page_system();
        nxi::window_system& window_system();

    private:
        ndb::initializer<ndb::sqlite> ndb_init_;
        nxs::network::client client_;
        std::thread client_thread_;

        nxi::command_system command_system_;
        nxi::window_system window_system_;
        nxi::page_system page_system_;
        nxi::module_system module_system_;
    };
} // nxi

#endif // CORE_H_NXI