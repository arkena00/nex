#ifndef NETWORK_CONNEXION_OUTPUT_H_NXS
#define NETWORK_CONNEXION_OUTPUT_H_NXS

#include <nxs/network/connexion.hpp>

namespace nxs{namespace network
{
    class output_connexion : virtual public connexion
    {
    public:
        virtual void connect(const std::string& ip, int port, int time_out = 0) = 0;

        virtual void on_connect(std::function<void()>) = 0;
        virtual void on_read(std::function<void(connexion::buffer_type&)>) = 0;
        virtual void on_send(std::function<void(size_t)>) = 0;
        virtual void on_error(std::function<void(const char*)>) = 0;
    };
}} // nxs::network

#endif // NETWORK_CONNEXION_OUTPUT_H_NXS
