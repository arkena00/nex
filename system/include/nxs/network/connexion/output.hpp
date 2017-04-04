#ifndef NETWORK_CONNEXION_OUTPUT_H_NXS
#define NETWORK_CONNEXION_OUTPUT_H_NXS

#include <nxs/network/connexion.hpp>
#include <string>
#include <functional>

namespace nxs{namespace network
{
    class output_connexion : virtual public connexion
    {
    public:
        virtual void connect(const std::string& ip, uint16_t port, int time_out = 0) = 0;
        virtual void on_connect(std::function<void()>) = 0;

    };
}} // nxs::network

#endif // NETWORK_CONNEXION_OUTPUT_H_NXS
