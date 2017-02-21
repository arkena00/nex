#ifndef NETWORK_PROTOCOL_NEX_H_NXS
#define NETWORK_PROTOCOL_NEX_H_NXS

#include <nxs/network/protocol/basic.hpp>

namespace nxs{namespace network
{
    template<io::type IO_Type>
    class nex : public basic_protocol<IO_Type>
    {
    public:
        nex(network::connexion& cnx) :
            basic_protocol<IO_Type>(cnx)
        {}

        void read();
        void send(const request&);
    };
}} // nxs::network

#include "nex.tpp"

#endif // NETWORK_PROTOCOL_NEX_H_NXS
