#ifndef CORE_H_NXI
#define CORE_H_NXI

#include <nxs/network/client.hpp>

#include <nxi/window_system.hpp>

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

    private:
        ndb::initializer<ndb::sqlite> ndb_init_;
        nxs::network::client client_;
        std::thread client_thread_;

        nxi::window_system window_system_;
    };
} // nxi

#endif // CORE_H_NXI