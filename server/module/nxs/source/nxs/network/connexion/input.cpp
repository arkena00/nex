#include <nxs/network/connexion/input.hpp>
#include <nxs/network/server.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/network/protocol/nex.hpp>
#include <nxs/network/protocol/http.hpp>
#include <nxs/network/protocol/ws.hpp>
#include <nxs/log.hpp>

using boost::asio::ip::tcp;

namespace nxs{namespace network
{
    input_connexion::input_connexion(server& server) :
        _server(server),
        _socket(server.ios())
    {
        _alive = 1;
    }
    input_connexion::~input_connexion()
    {
        nxs_log << "connexion closed " << _ip_client << id() << log::network;
    }

    // load connexion
    void input_connexion::load()
    {
        // client ip
        _ip_client = _socket.remote_endpoint().address().to_string();
        _ip_local = _socket.local_endpoint().address().to_string();

        //nxs::event("connexion_open", "id=" + to_string(_id) + ";ip=" + _ip_client + ";");
        nxs_log << "connexion incoming " << _ip_client << id() << log::network;
        read();
    }

    // socket read
    void input_connexion::socket_read(const boost::system::error_code& status, size_t bytes_transferred)
    {
        buffer().reserve(bytes_transferred);

        if (!_alive) return;
        if (!status)
        {
            try {
            // detect protocol
            if (!has_protocol()) protocol_detect(buffer());
           protocol().read();

            // read next data
            read();

            } catch (const std::exception& e)
            {
                nxs_log << e.what() << log::network;
                socket_close(status);
            }
        }
        else socket_close(status);
    }
    // socket send
    void input_connexion::socket_send(const boost::system::error_code& status, size_t bytes_transferred)
    {
        if (!_alive) return;
        if (!status)
        {
        }
        else socket_close(status);
    }
    // socket close
    void input_connexion::socket_close(const boost::system::error_code& status)
    {
        close();
    }

    // data_read
    void input_connexion::read()
    {
        if (!_alive) return;
        _socket.async_read_some(boost::asio::buffer(buffer().address(), buffer().capacity()),
        boost::bind(&input_connexion::socket_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
        );
    }

    void input_connexion::send(const char* data, size_t data_size)
    {
        if (!_alive) return;
        boost::asio::async_write(_socket,
        boost::asio::buffer(data, data_size),
        boost::bind(&input_connexion::socket_send, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
        );
    }

    // close connexion
    void input_connexion::close()
    {
        _alive = 0;
        _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        _socket.close();
        _server.connexion_close(id());
    }

    void input_connexion::protocol_detect(const buffer_type& buffer)
    {
        // nex
        if (strncmp(buffer.data(), "NEX", 3) == 0) protocol_set<nex<io::input>>();
        // http
        else if (strncmp(buffer.data(), "GET", 3) == 0 || strncmp(buffer.data(), "POST", 4) == 0)
        {
            // ws
            std::string str_data = std::string(buffer.data(), buffer.size());
            if (str_data.find("Sec-WebSocket-Key:") != std::string::npos) protocol_set<ws>();
            protocol_set<http<io::input>>();
        }
        // no protocol found, disconnect
        else nxs_error << "protocol_unknown\n" << std::string(buffer.data(), buffer.size());
    }

    boost::asio::ip::tcp::socket& input_connexion::socket() { return _socket; }
    const std::string& input_connexion::ip_client() const { return _ip_client; }
    const std::string& input_connexion::ip_local() const { return _ip_local; }
}} // nxs::network
