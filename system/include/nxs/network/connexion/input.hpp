#ifndef NETWORK_CONNEXION_INPUT_H_NXS
#define NETWORK_CONNEXION_INPUT_H_NXS

#include <nxs/network/socket.hpp>
#include <nxs/network/connexion/basic.hpp>

namespace nxs{namespace network
{
    class input_connexion : public basic_connexion<io::input>
    {
    public:
        input_connexion(asio::io_service& ios);

        void accept(asio::ip::tcp::acceptor&, const std::function<void(const asio::error_code&)>&);
        void load();
    };
}} // nxs::network

#endif // NETWORK_CONNEXION_INPUT_H_NXS
