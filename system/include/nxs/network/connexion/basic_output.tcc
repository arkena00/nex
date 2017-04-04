#include <nxs/network/connexion/output.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/network/connexion/basic.hpp>

namespace nxs{namespace network
{
    using boost::asio::ip::tcp;

    template<class Protocol>
    basic_output_connexion<Protocol>::basic_output_connexion(connexion_manager<output_connexion>& client) :
            basic_connexion(client.ios(), protocol::create<Protocol>(*this)),
            _client(client),
            _timer(client.ios())
    {
        _ip = "127.0.0.1";
        _port = 50;
    }

    // callback
    template<class Protocol>
    void basic_output_connexion<Protocol>::on_connect(std::function<void()> fn)
    {
        _on_connect = fn;
    }

    template<class Protocol>
    void basic_output_connexion<Protocol>::connect(const std::string& ip, uint16_t port, int time_out)
    {
        _ip   = ip;
        _port = port;

        auto socket_connect = [this](const boost::system::error_code& err)
        {
            if (!err)
            {
                _alive = 1;
                if (_on_connect)
                {
                    nxs_log << "connexion open" << _ip << ":" << _port << basic_connexion<io::output>::id() << log::network;
                    _on_connect();
                }

                // start read
                this->read();

            } //else this->error(status);
        };

        tcp::endpoint endpoint(boost::asio::ip::address::from_string(_ip), _port);
        _socket.async_connect(endpoint, socket_connect);
    }

    template<class Protocol>
    void basic_output_connexion<Protocol>::sync_connect(const std::string& ip, uint16_t port)
    {
        _ip   = ip;
        _port = port;
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(_ip), _port);
        _socket.connect(endpoint);
        _alive = 1;
        nxs_log << "connexion open" << _ip << ":" << _port << basic_connexion<io::output>::id() << log::network;
    }

    template<class Protocol>
    void basic_output_connexion<Protocol>::sync_read()
    {
        if (!_alive) return;

        while (1)
        {
            boost::system::error_code error;

            int data_size = _socket.read_some(boost::asio::buffer(basic_connexion<io::output>::buffer().address(),
                                                                  basic_connexion<io::output>::buffer().capacity()),
                                              error);
            basic_connexion<io::output>::buffer().reserve(data_size);
            basic_connexion<io::output>::protocol().read();
            if (basic_connexion<io::output>::protocol().transfer_complete() || error) break;
        }
    }

}} // nxs::network
