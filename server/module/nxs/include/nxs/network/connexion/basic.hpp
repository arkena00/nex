#ifndef NETWORK_CONNEXION_BASIC_H_NXS
#define NETWORK_CONNEXION_BASIC_H_NXS

#include <nxs/share.hpp>
#include <nxs/setup/connexion.hpp>
#include <nxs/network/connexion.hpp>
#include <nxs/network/socket.hpp>
#include <nxs/network/io.hpp>
#include <nxs/network/buffer.hpp>
#include <nxs/network/data.hpp>
#include <memory>
#include <string>
#include <deque>

namespace nxs{namespace network
{
    template<io::type IO_Type>
    class basic_connexion : virtual public connexion
    {
    public:
        using buffer_type = setup<connexion>::buffer_type;

    private:
        static size_t id_;

        size_t _id;

        void socket_send(const boost::system::error_code& status, size_t bytes_transferred);

    protected:
        bool _alive;
        boost::asio::ip::tcp::socket _socket;
        std::unique_ptr<network::protocol> _protocol;
        buffer_type _buffer;

        std::deque<network::data_ptr> _output_buffer;

        template<class Protocol>
        void protocol_set();

    public:
        basic_connexion(boost::asio::io_service& ios, std::unique_ptr<network::protocol> = nullptr);

        virtual ~basic_connexion() = default;
        virtual void read() = 0;
        virtual void send(const char* data, size_t data_size) = 0;

        void send(network::data_ptr);
        void send();

        void send(const std::string& data);

        size_t id() const override;
        constexpr io::type iotype() const;
        bool is_alive() const;
        network::protocol& protocol() override;
        buffer_type& buffer() override;
        bool has_protocol() const;

        boost::asio::ip::tcp::socket& socket();
    };
}} // nxs::network

#include "basic.tcc"

#endif // NETWORK_CONNEXION_BASIC_H_NXS
