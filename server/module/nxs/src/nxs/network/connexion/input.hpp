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
    #ifndef NXS_IMPORTED
        boost::asio::ip::tcp::socket _socket;
    #endif

        std::string _ip_client;
        std::string _ip_local;

        void socket_read(const boost::system::error_code& status, size_t bytes_transferred);
        void socket_send(const boost::system::error_code& status, size_t bytes_transferred);
        void socket_close(const boost::system::error_code& status);

    public:
        input_connexion(server& server);
        ~input_connexion();

        void load();
        void close();

        boost::asio::ip::tcp::socket& socket();

        const std::string& ip_client() const;
        const std::string& ip_local() const;

        virtual void read();
        virtual void send(const char* data, int data_size);

        void protocol_detect(const buffer_type& buffer);
    };
}} // nxs::network

#endif // NETWORK_CONNEXION_INPUT_H_NXS
