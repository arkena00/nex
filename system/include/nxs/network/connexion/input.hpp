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
        server& _server;

    public:
        input_connexion(server& server);
        ~input_connexion();

        void load();
    };
}} // nxs::network

#endif // NETWORK_CONNEXION_INPUT_H_NXS
