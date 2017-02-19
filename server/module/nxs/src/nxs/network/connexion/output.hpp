#ifndef NETWORK_CONNEXION_OUTPUT_H_NXS
#define NETWORK_CONNEXION_OUTPUT_H_NXS

#include <nxs/network/socket.hpp>
#include <nxs/network/connexion.hpp>

namespace nxs{namespace network
{
    class output_connexion : public connexion
    {
    private:
        static boost::asio::io_service ios;

        boost::asio::ip::tcp::socket _socket;
        std::string _ip;
        int _port;
        boost::asio::deadline_timer _timer;
        std::function<void()> _callback_connect;
        std::function<void(connexion::buffer_type)> _callback_data_read;
        std::function<void(size_t)> _callback_data_send;
        std::function<void(const char*)> _callback_error;

        void init();

        void socket_connect(const boost::system::error_code& status);
        void socket_read(const boost::system::error_code& status, size_t bytes_transferred);
        void socket_send(const boost::system::error_code& status, size_t bytes_transferred);
        void socket_error(const boost::system::error_code& status);

    public:
        output_connexion();
        output_connexion(std::string ip, int port);
        ~output_connexion();

        void connect(std::string ip, int port, int time_out = 5);
        void sync_connect(std::string ip, int port);

        void connect_callback_set(std::function<void()>);
        void data_read_callback_set(std::function<void(connexion::buffer_type)>);
        void data_send_callback_set(std::function<void(size_t)>);
        void error_callback_set(std::function<void(const char*)>);

        virtual void read();
        void sync_data_read();
        virtual void send(const char* data, int data_size);

        void run();

        std::string ip();
        int port();

        static output_connexion* create();

    };
}} // nxs::network

#endif // NETWORK_CONNEXION_OUTPUT_H_NXS
