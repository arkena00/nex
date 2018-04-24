#ifndef NETWORK_SERVER_H_NXS
#define NETWORK_SERVER_H_NXS

#include <nxs/share.hpp>
#include <nxs/network/connexion/manager.hpp>

namespace nxs{namespace network
{
    class input_connexion;

    class server : public connexion_manager<input_connexion>
    {
    private:
        uint16_t _port;
        asio::ip::tcp::acceptor _acceptor;

        void listen();

    public:
        server(uint16_t port);

        void run() override;
    };
}} // nxs::network

#endif // NETWORK_SERVER_H_NXS
