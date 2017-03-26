#ifndef NETWORK_CONNEXION_BASIC_OUTPUT_H_NXS
#define NETWORK_CONNEXION_BASIC_OUTPUT_H_NXS

#include <nxs/network/socket.hpp>
#include <nxs/network/connexion/basic.hpp>
#include <nxs/network/connexion/output.hpp>

namespace nxs{namespace network
{
    template<class Protocol>
    class NXS_SHARED basic_output_connexion : public basic_connexion<io::output>, public output_connexion
    {
    private:
        connexion_manager<output_connexion>& _client;

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

    public:
        basic_output_connexion(connexion_manager<output_connexion>&);
        ~basic_output_connexion();

        void connect(const std::string& ip, int port, int time_out = 5) override;
        void sync_connect(const std::string& ip, int port);

        void on_connect(std::function<void()>) override;
        void on_read(std::function<void(connexion::buffer_type&)>) override;
        void on_send(std::function<void(size_t)>) override;
        void on_error(std::function<void(const char*)>) override;

        void read() override;
        void sync_read();
        void send(const char* data, size_t data_size);

        const std::string& ip() const;
        int port() const;
    };
}} // nxs::network

#ifndef NXS_IMPORTED
    #include "basic_output.tcc"
#endif

#endif // NETWORK_CONNEXION_BASIC_OUTPUT_H_NXS
