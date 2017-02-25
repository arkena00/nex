#ifndef NETWORK_CONNEXION_OUTPUT_H_NXS
#define NETWORK_CONNEXION_OUTPUT_H_NXS

#include <nxs/network/socket.hpp>
#include <nxs/network/connexion/basic.hpp>

namespace nxs{namespace network
{
    class client;

    class NXS_SHARED output_connexion : public basic_connexion<io::output>
    {
    private:
        client& _client;
    #ifndef NXS_IMPORTED
        boost::asio::ip::tcp::socket _socket;
        boost::asio::deadline_timer _timer;

        std::string _ip;
        int _port;
        std::function<void()> _on_connect;
        std::function<void(connexion::buffer_type&)> _on_read;
        std::function<void(size_t)> _on_send;
        std::function<void(const char*)> _on_error;

        void socket_connect(const boost::system::error_code& status);
        void socket_read(const boost::system::error_code& status, size_t bytes_transferred);
        void socket_send(const boost::system::error_code& status, size_t bytes_transferred);
        void socket_error(const boost::system::error_code& status);
    #endif
    public:
        output_connexion(client&);
        ~output_connexion();

        void load();

        void connect(std::string ip, int port, int time_out = 5);
        void sync_connect(std::string ip, int port);

        void on_connect(std::function<void()>);
        void on_read(std::function<void(connexion::buffer_type&)>);
        void on_send(std::function<void(size_t)>);
        void on_error(std::function<void(const char*)>);

        void read() override;
        void sync_read();
        virtual void send(const char* data, int data_size);

        const std::string& ip() const;
        int port() const;
    };
}} // nxs::network

#endif // NETWORK_CONNEXION_OUTPUT_H_NXS
