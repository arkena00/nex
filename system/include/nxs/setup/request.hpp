#ifndef NETWORK_REQUEST_SETUP_H_NXS
#define NETWORK_REQUEST_SETUP_H_NXS

#include <nxs/setup.hpp>

namespace nxs
{
    class request;

    template<>
    struct setup<request>
    {
        constexpr static float version = 1.0;
        using linear_type = std::string;
    };
} // nxs

#endif // NETWORK_REQUEST_SETUP_H_NXS
