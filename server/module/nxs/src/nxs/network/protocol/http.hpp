#ifndef NETWORK_PROTOCOL_HTTP_H_NXS
#define NETWORK_PROTOCOL_HTTP_H_NXS

#include <nxs/network/protocol.hpp>

namespace nxs{namespace network
{
    class http : public protocol
    {
    public:
        http(network::connexion* cnx);

        virtual void read();
        virtual void send(const request&);

        void send_string(const std::string&);
    };
}} // nxs::network

#endif // NETWORK_PROTOCOL_HTTP_H_NXS
