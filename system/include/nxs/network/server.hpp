#ifndef NETWORK_SERVER_H_NXS
#define NETWORK_SERVER_H_NXS

#include <nxs/share.hpp>
#include <nxs/network/connexion/manager.hpp>

namespace nxs{namespace network
{
    class input_connexion;

    class NXS_SHARED server : public connexion_manager<input_connexion>
    {
    private:
        uint16_t _port;

        boost::asio::ip::tcp::acceptor _acceptor;

        void listen();
        void accept(input_connexion* cnx, const boost::system::error_code& status);

    public:
        server(uint16_t port);
        ~server();

        void run() override;
    };
}} // nxs::network

#endif // NETWORK_SERVER_H_NXS
