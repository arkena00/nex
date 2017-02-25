#ifndef CORE_H_NXI
#define CORE_H_NXI

#include <nxs/network/client.hpp>

namespace nxi
{
    class core
    {
    private:
        nxs::network::client _client;

    public:
        core();

        nxs::network::client& client();
    };
} // nxi

#endif // CORE_H_NXI
