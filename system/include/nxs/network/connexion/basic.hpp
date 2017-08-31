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
#include <nxs/network/error_code.hpp>

namespace nxs{namespace network
{
    template<io::type IO_Type>
    class basic_connexion : virtual public connexion
    {
    private:
        size_t _id;

        std::unique_ptr<network::protocol> _protocol;
        buffer_type _buffer;
        size_t _output_progress_size;
        std::deque<std::tuple<std::shared_ptr<data>, std::function<void()>>> _output_data;

        std::function<void()> _on_read;
        std::function<void(const network::data&)> _on_send;
        std::function<void(const network::error_code&)> _on_close;

        template<class Protocol>
        void protocol_set();
        void protocol_detect();

    protected:
        bool _alive;
        boost::asio::ip::tcp::socket _socket;

        void read();
        void send();
        void close(const network::error_code&);

    public:
        basic_connexion(boost::asio::io_service& ios, std::unique_ptr<network::protocol> = nullptr);
        ~basic_connexion();

        void send(std::shared_ptr<data>, std::function<void()> = nullptr) override;

        void on_read(std::function<void()>) override;
        void on_send(std::function<void(const network::data&)>, size_t progress_size) override;
        void on_close(std::function<void(const network::error_code&)>) override;

        size_t id() const override;
        constexpr io::type iotype() const;
        bool is_alive() const override;
        network::protocol& protocol() override;
        buffer_type& buffer() override;
        bool has_protocol() const;
        std::string ip() const;
        uint16_t port() const;
    };
}} // nxs::network

#include "basic.tcc"

#endif // NETWORK_CONNEXION_BASIC_H_NXS
