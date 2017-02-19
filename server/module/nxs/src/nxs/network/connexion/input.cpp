#include <nxs/network/connexion/input.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/log.hpp>

using boost::asio::ip::tcp;

namespace nxs{namespace network
{
    int input_connexion::id_ = 0;
    std::map<int, input_connexion*> input_connexion::list_;

    input_connexion::input_connexion(boost::asio::io_service& ios) :
        connexion(connexion::input),
        _socket(ios)
    {
        id_++;
        _id = id_;
        _alive = 1;
    }
    input_connexion::~input_connexion()
    {
        // delete cnx pointer
        input_connexion::list_.erase(_id);
        // delete user pointer
        nxs_log << "connexion closed " << _ip_client << _id << log::network;
    }

    // load connexion
    void input_connexion::load()
    {
        // client ip
        _ip_client = _socket.remote_endpoint().address().to_string();
        _ip_local = _socket.local_endpoint().address().to_string();

        // link id to cnx pointer
        input_connexion::list_[_id] = this;

        //nxs::event("connexion_open", "id=" + to_string(_id) + ";ip=" + _ip_client + ";");
        nxs_log << "connexion incoming " << _ip_client << _id << log::network;
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
        _alive = 0;
        _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        _socket.close();
        delete this;
    }

    // data_read
    void input_connexion::read()
    {
        if (!_alive) return;
        _socket.async_read_some(boost::asio::buffer(buffer().address(), buffer().capacity()),
        boost::bind(&input_connexion::socket_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
        );
    }

    void input_connexion::send(const char* data, int data_size)
    {
        if (!_alive) return;
        boost::asio::async_write(_socket,
        boost::asio::buffer(data, data_size),
        boost::bind(&input_connexion::socket_send, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
        );
    }

    // close connexion
    void input_connexion::close() {}

    input_connexion* input_connexion::create(boost::asio::io_service& ios)
    {
        return new input_connexion(ios);
    }

    boost::asio::ip::tcp::socket& input_connexion::socket() { return _socket; }
    const std::string& input_connexion::ip_client() const { return _ip_client; }
    const std::string& input_connexion::ip_local() const { return _ip_local; }
}} // nxs::network
