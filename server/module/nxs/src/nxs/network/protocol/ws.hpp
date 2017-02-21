#ifndef NETWORK_PROTOCOL_WS_H_NXS
#define NETWORK_PROTOCOL_WS_H_NXS

#include <nxs/network/protocol/basic.hpp>

namespace nxs{namespace network
{
    class ws : public basic_protocol<io::input>
    {
    private:
        bool _handshake_done;
    public:
        ws(network::connexion& cnx);

        virtual void read();
        virtual void send(const request&);

        void process_handshake(const char* data, size_t data_received);
        std::string data_decode(const char* data, size_t data_received);
        void data_send(const char* data, size_t data_size);
    };
}} // nxs::network


#endif // NETWORK_PROTOCOL_WS_H_NXS

