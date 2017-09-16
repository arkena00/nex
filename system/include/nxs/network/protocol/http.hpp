#ifndef NETWORK_PROTOCOL_HTTP_H_NXS
#define NETWORK_PROTOCOL_HTTP_H_NXS

#include <nxs/network/protocol/basic.hpp>

namespace nxs{namespace network
{
    template<io::type IO_Type>
    class http : public basic_protocol<IO_Type>
    {
    public:
        bool _mm = false;

        http(network::connexion& cnx) :
            basic_protocol<IO_Type>(cnx)
        {}

        void read() override;
        void send() override;

        void send_string(std::string&&);
        void mm_send(const std::string&);
    };

    template<> void http<io::input>::read();
    template<> void http<io::input>::send();
    template<> void http<io::input>::send_string(std::string&&);
    template<> void http<io::input>::mm_send(const std::string& data);

    template<> void http<io::output>::read();
    template<> void http<io::output>::send();
}} // nxs::network

#endif // NETWORK_PROTOCOL_HTTP_H_NXS
