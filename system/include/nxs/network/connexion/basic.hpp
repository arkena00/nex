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
        size_t _id;

        std::function<void()> _on_read;
        std::function<void(const network::data&)> _on_send;
        std::function<void(const std::string&)> _on_error;

    protected:
        std::string _ip;
        uint16_t _port;
        bool _alive;
        boost::asio::ip::tcp::socket _socket;
        std::unique_ptr<network::protocol> _protocol;
        buffer_type _buffer;
        size_t _output_progress_size;
        std::deque<network::data_ptr> _output_data;

        template<class Protocol>
        void protocol_set();
        void protocol_detect();

        void read();
        void send();

    public:
        basic_connexion(boost::asio::io_service& ios, std::unique_ptr<network::protocol> = nullptr);
        virtual ~basic_connexion() = default;

        void send(network::data_ptr);

        void on_read(std::function<void()>) override;
        void on_send(std::function<void(const network::data&)>, size_t progress_size) override;
        void on_error(std::function<void(const std::string&)>) override;

        size_t id() const override;
        constexpr io::type iotype() const;
        bool is_alive() const;
        network::protocol& protocol() override;
        buffer_type& buffer() override;
        bool has_protocol() const;
        const std::string& ip() const;
        uint16_t port() const;

        boost::asio::ip::tcp::socket& socket();
    };
}} // nxs::network

#include "basic.tcc"

#endif // NETWORK_CONNEXION_BASIC_H_NXS
