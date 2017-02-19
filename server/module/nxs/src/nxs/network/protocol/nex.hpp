#ifndef NETWORK_PROTOCOL_NEX_H_NXS
#define NETWORK_PROTOCOL_NEX_H_NXS

#include <nxs/network/protocol.hpp>
#include <nxs/network/header.hpp>

namespace nxs{namespace network
{
    class nex : public protocol
    {
    public:
        nex(network::connexion* cnx);

        virtual void read();
        virtual void send(const request&);
    };
}} // nxs::network

#endif // NETWORK_PROTOCOL_NEX_H_NXS
