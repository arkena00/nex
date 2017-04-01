#include <nxs/network/connexion/output.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/network/connexion/basic.hpp>
#include <nxs/network/protocol/nex.hpp>

namespace nxs{namespace network
{
    using boost::asio::ip::tcp;

    template<class Protocol>
    basic_output_connexion<Protocol>::basic_output_connexion(connexion_manager<output_connexion>& client) :
            basic_connexion(client.ios(), protocol::create<Protocol>(*this)),
            _client(client),
            _timer(client.ios()),
            _ip("127.0.0.1"),
            _port(50)
    {}

    template<class Protocol>
    basic_output_connexion<Protocol>::~basic_output_connexion()
    {
        _socket.close();
        nxs_log << "connexion closed" << _ip << ":" << _port << basic_connexion<io::output>::id() << log::network;
    }

    // callback
    template<class Protocol> void basic_output_connexion<Protocol>::on_connect(std::function<void()> fn) { _on_connect = fn; }
    template<class Protocol> void basic_output_connexion<Protocol>::on_read(std::function<void(output_connexion&)> fn) { _on_read = fn; }
    template<class Protocol> void basic_output_connexion<Protocol>::on_send(std::function<void(size_t)> fn) { _on_send = fn; }
    template<class Protocol> void basic_output_connexion<Protocol>::on_error(std::function<void(const char*)> fn) { _on_error = fn; }

    // socket connect
    template<class Protocol>
    void basic_output_connexion<Protocol>::socket_connect(const boost::system::error_code& status)
    {
        if (!status)
        {
            _alive = 1;
            if (_on_connect)
            {
                nxs_log << "connexion open" << _ip << ":" << _port << basic_connexion<io::output>::id() << log::network;
                _on_connect();
            }

        } else socket_error(status);
    }

    // socket read
    template<class Protocol>
    void
    basic_output_connexion<Protocol>::socket_read(const boost::system::error_code& status, size_t bytes_transferred)
    {
        if (!status && _alive)
        {
            try
            {
                basic_connexion<io::output>::buffer().reserve(bytes_transferred);
                basic_connexion<io::output>::protocol().read();
                if (_on_read) _on_read(*this);
                // read next data
                read();

            } catch (const std::exception& e)
            {
                nxs_log << e.what() << log::network;
                socket_error(status);
            }
        }
        else socket_error(status);
    }

    // socket send
    template<class Protocol>
    void
    basic_output_connexion<Protocol>::socket_send(const boost::system::error_code& status, size_t bytes_transferred)
    {
        if (!status && _alive)
        {
            if (_on_send) _on_send(bytes_transferred);
        }
        else socket_error(status);
    }

    // socket error
    template<class Protocol>
    void basic_output_connexion<Protocol>::socket_error(const boost::system::error_code& status)
    {
        _alive = 0;
        nxs_log << "socket error" << status.message() << log::network;
        if (_on_error) _on_error(status.message().c_str());
    }

    template<class Protocol>
    void basic_output_connexion<Protocol>::connect(const std::string& ip, int port, int time_out)
    {
        _ip   = ip;
        _port = port;

        tcp::endpoint endpoint(boost::asio::ip::address::from_string(_ip), _port);
        _socket.async_connect(endpoint, boost::bind(&basic_output_connexion<Protocol>::socket_connect, this,
                                                    boost::asio::placeholders::error));


    }

    template<class Protocol>
    void basic_output_connexion<Protocol>::sync_connect(const std::string& ip, int port)
    {
        _ip   = ip;
        _port = port;
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(_ip), _port);
        _socket.connect(endpoint);
        _alive = 1;
        nxs_log << "connexion open" << _ip << ":" << _port << basic_connexion<io::output>::id() << log::network;
    }

    // data_read
    template<class Protocol>
    void basic_output_connexion<Protocol>::read()
    {
        if (!_alive) return;
        //clear buffer
        _socket.async_read_some(boost::asio::buffer(basic_connexion<io::output>::buffer().address(),
                                                    basic_connexion<io::output>::buffer().capacity()),
                                boost::bind(&basic_output_connexion<Protocol>::socket_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
        );
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

    template<class Protocol>
    void basic_output_connexion<Protocol>::send(const char* data, size_t data_size)
    {
        if (!_alive) return;

        boost::asio::async_write(_socket, boost::asio::buffer(data, data_size),
                                 boost::bind(&basic_output_connexion<Protocol>::socket_send, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred)
        );
    }


    template<class Protocol>
    const std::string& basic_output_connexion<Protocol>::ip() const
    {
        return _ip;
    }

    template<class Protocol>
    int basic_output_connexion<Protocol>::port() const
    {
        return _port;
    }
}} // nxs::network
