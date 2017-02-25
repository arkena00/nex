#include <nxs/network/connexion/output.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/network/connexion/basic.hpp>
#include <nxs/network/buffer.hpp>
#include <nxs/network/protocol/nex.hpp>
#include <nxs/network/client.hpp>

namespace nxs{namespace network
{
    using boost::asio::ip::tcp;

    output_connexion::output_connexion(client& client) :
        basic_connexion(protocol::create<network::nex<io::output>>(*this)),
        _client(client),
        _socket(client.ios()),
        _timer(client.ios()),
        _ip("127.0.0.1"),
        _port(50)
    {}

    output_connexion::~output_connexion()
    {
        _socket.close();
        nxs_log << "connexion closed" << _ip << ":" << _port << id() << log::network;
    }

    void output_connexion::load() {}

    // callback
    void output_connexion::on_connect(std::function<void()> fn) { _on_connect = fn; }
    void output_connexion::on_read(std::function<void(connexion::buffer_type&)> fn) { _on_read = fn; }
    void output_connexion::on_send(std::function<void(size_t)> fn) { _on_send = fn; }
    void output_connexion::on_error(std::function<void(const char*)> fn) { _on_error = fn; }

    // socket connect
    void output_connexion::socket_connect(const boost::system::error_code& status)
    {
        if (!status)
        {
            _alive = 1;
            if (_on_connect)
            {
                nxs_log << "connexion open" << _ip << ":" << _port << id() << log::network;
                _on_connect();
            }
            read();
        }
        else socket_error(status);
    }

    // socket read
    void output_connexion::socket_read(const boost::system::error_code& status, size_t bytes_transferred)
    {
        if (!status && _alive)
        {
            buffer().reserve(bytes_transferred);
            if (_on_read) _on_read(buffer());
            // read next data
            read();
        }
        else socket_error(status);
    }
    // socket send
    void output_connexion::socket_send(const boost::system::error_code& status, size_t bytes_transferred)
    {
        if (!status && _alive)
        {
            if (_on_send) _on_send(bytes_transferred);
        }
        else socket_error(status);
    }
    // socket error
    void output_connexion::socket_error(const boost::system::error_code& status)
    {
        _alive = 0;
        if (_on_error) _on_error(status.message().c_str());
    }

    void output_connexion::connect(std::string ip, int port, int time_out)
    {
        _ip = ip;
        _port = port;

        tcp::endpoint endpoint(boost::asio::ip::address::from_string(_ip), _port);
        _socket.async_connect(endpoint, boost::bind(&output_connexion::socket_connect, this, boost::asio::placeholders::error));
    }

    void output_connexion::sync_connect(std::string ip, int port)
    {
        _ip = ip;
        _port = port;
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(_ip), _port);
        _socket.connect(endpoint);
        _alive = 1;
        nxs_log << "connexion open" << _ip << ":" << _port << id() << log::network;
    }

    // data_read
    void output_connexion::read()
    {
        if (!_alive) return;
        //clear buffer
        _socket.async_read_some(boost::asio::buffer(buffer().address(), buffer().capacity()),
                                boost::bind(&output_connexion::socket_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
        );
    }

    void output_connexion::sync_read()
    {
        if (!_alive) return;

        while (1)
        {
            boost::system::error_code error;

            int data_size = _socket.read_some(boost::asio::buffer(buffer().address(), buffer().capacity()), error);
            buffer().reserve(data_size);
            protocol().read();
            if (protocol().transfer_complete() || error) break;
        }
    }

    void output_connexion::send(const char* data, int data_size)
    {
        if (!_alive) return;
        boost::asio::async_write(_socket, boost::asio::buffer(data, data_size),
                                 boost::bind(&output_connexion::socket_send, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred)
        );
    }

    const std::string& output_connexion::ip() const { return _ip; }
    int output_connexion::port() const { return _port; }
}} // nxs::network
