#ifndef NETWORK_PROTOCOL_HTTP_H_NXS
#define NETWORK_PROTOCOL_HTTP_H_NXS

#include <nxs/network/protocol.hpp>

namespace nxs{namespace network
{
    class http : public protocol
    {
    public:
        http(network::connexion* cnx);

        virtual void input_read(const buffer_type&);
        virtual void input_send(const request&);
        virtual void output_read(const buffer_type&);
        virtual void output_send(const request&);

        void send_string(const std::string&);
    };
}} // nxs::network

#endif // NETWORK_PROTOCOL_HTTP_H_NXS

