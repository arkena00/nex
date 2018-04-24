#include <nxs/network/protocol.hpp>

namespace nxs{namespace network
{
    using asio::ip::tcp;

    template<class Protocol>
    basic_output_connexion<Protocol>::basic_output_connexion(asio::io_service& ios) :
        basic_connexion(ios, protocol::create<Protocol>(static_cast<output_connexion&>(*this))),
        _timer(ios)
    {}

    // callback
    template<class Protocol>
    void basic_output_connexion<Protocol>::on_connect(std::function<void()> fn)
    {
        _on_connect = fn;
    }

    template<class Protocol>
    void basic_output_connexion<Protocol>::connect(const std::string& ip, uint16_t port, int time_out)
    {
        auto socket_connect = [this](const network::error_code& err)
        {
            if (!err)
            {
                _alive = true;
                if (_on_connect) _on_connect();

                this->read();
            }
            else this->close(err);
        };

        tcp::endpoint endpoint(asio::ip::address::from_string(ip), port);
        _socket.close();
        _socket.async_connect(endpoint, socket_connect);
    }

    template<class Protocol>
    void basic_output_connexion<Protocol>::sync_connect(const std::string& ip, uint16_t port)
    {
        tcp::endpoint endpoint(asio::ip::address::from_string(ip), port);
        _socket.connect(endpoint);
        _alive = true;
        nxs_log << "connexion open" << basic_connexion::ip() << ":" << basic_connexion::port() << basic_connexion::id() << log::network;
    }

    template<class Protocol>
    void basic_output_connexion<Protocol>::sync_read()
    {
        if (!_alive) return;

        while (1)
        {
            network::error_code error;

            size_t data_size = _socket.read_some(asio::buffer(basic_connexion<io::output>::buffer().address(),
                                                                  basic_connexion<io::output>::buffer().capacity()),
                                              error);
            basic_connexion<io::output>::buffer().reserve(data_size);
            basic_connexion<io::output>::protocol().read();
            if (basic_connexion<io::output>::protocol().transfer_complete() || error) break;
        }
    }

}} // nxs::network
