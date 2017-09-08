#ifndef CORE_H_NXI
#define CORE_H_NXI

#include <nxs/network/client.hpp>

#include <Nazara/Core/Initializer.hpp>
#include <NDK/Sdk.hpp>

namespace nxi
{
    class core
    {
    private:
        nxs::network::client m_client;
        std::thread m_client_thread;

        Nz::Initializer<Ndk::Sdk> nazara_;

    public:
        core();
        ~core();
        core(const core&) = delete;

        nxs::network::client& client();
    };
} // nxi

#endif // CORE_H_NXI
