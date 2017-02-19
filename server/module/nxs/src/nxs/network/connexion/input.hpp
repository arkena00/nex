#ifndef NETWORK_CONNEXION_INPUT_H_NXS
#define NETWORK_CONNEXION_INPUT_H_NXS

#include <nxs/network/socket.hpp>
#include <nxs/network/connexion.hpp>

namespace nxs{namespace network
{
    class protocol;

    class input_connexion : public connexion
    {
    private:
        boost::asio::ip::tcp::socket _socket;

        std::string _ip_client;
        std::string _ip_local;

        void socket_read(const boost::system::error_code& status, size_t bytes_transferred);
        void socket_send(const boost::system::error_code& status, size_t bytes_transferred);
        void socket_close(const boost::system::error_code& status);

    public:
        static int id_;
        static std::map<int, input_connexion*> list_;

        input_connexion(boost::asio::io_service& ios);
        virtual ~input_connexion();

        void load();
        void close();

        boost::asio::ip::tcp::socket& socket();

        const std::string& ip_client() const;
        const std::string& ip_local() const;

        virtual void read();
        virtual void send(const char* data, int data_size);

        static input_connexion* create(boost::asio::io_service& ios);
        static const input_connexion& get(int id);
        static bool exist(int id);
    };
}} // nxs::network

#endif // NETWORK_CONNEXION_INPUT_H_NXS
