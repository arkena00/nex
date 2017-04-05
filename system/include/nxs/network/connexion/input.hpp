#ifndef NETWORK_CONNEXION_INPUT_H_NXS
#define NETWORK_CONNEXION_INPUT_H_NXS

#include <nxs/network/socket.hpp>
#include <nxs/network/connexion/basic.hpp>

namespace nxs{namespace network
{
    class server;

    class input_connexion : public basic_connexion<io::input>
    {
    private:
        boost::asio::ip::tcp::acceptor _acceptor;

    public:
        input_connexion(boost::asio::io_service& ios, uint16_t port);
        ~input_connexion();

        void accept(const std::function<void(const boost::system::error_code&)>&);
        void load();
    };
}} // nxs::network

#endif // NETWORK_CONNEXION_INPUT_H_NXS
