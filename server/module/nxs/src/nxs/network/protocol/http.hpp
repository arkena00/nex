#ifndef NETWORK_PROTOCOL_HTTP_H_NXS
#define NETWORK_PROTOCOL_HTTP_H_NXS

#include <nxs/network/protocol/basic.hpp>

namespace nxs{namespace network
{
    template<io::type IO_Type>
    class NXS_SHARED http : public basic_protocol<IO_Type>
    {
    public:
        http(network::connexion& cnx) :
            basic_protocol<IO_Type>(cnx)
        {}

        virtual void read();
        virtual void send(const request&);

        void send_string(const std::string&);
    };

    template<> void http<io::input>::read();
    template<> void http<io::input>::send(const request&);
    template<> void http<io::input>::send_string(const std::string&);

    template<> void http<io::output>::read();
    template<> void http<io::output>::send(const request&);
}} // nxs::network

#endif // NETWORK_PROTOCOL_HTTP_H_NXS
