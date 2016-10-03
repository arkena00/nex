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

        virtual void input_read(const buffer_type&);
        virtual void input_send(const request&);
        virtual void output_read(const buffer_type&);
        virtual void output_send(const request&);
    };
}} // nxs::network

#endif // NETWORK_PROTOCOL_NEX_H_NXS
