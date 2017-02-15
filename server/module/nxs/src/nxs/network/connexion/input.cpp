#include <nxs/network/connexion/input.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/log.hpp>

using namespace std;
using boost::asio::ip::tcp;
using nxs::network::input_connexion;

int input_connexion::id_ = 0;
map<int, input_connexion*> input_connexion::list_;

input_connexion::input_connexion(boost::asio::io_service& ios) : connexion(), _socket(ios), _protocol(nullptr)
{
    id_++;
    _id = id_;
    _iotype = connexion::input;
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
    data_read();
}

// socket read
void input_connexion::socket_read(const boost::system::error_code& status, size_t bytes_transferred)
{
    _buffer.size(bytes_transferred);

    if (!_alive) return;
    if (!status)
    {
        try {
        // detect protocol
        if (_protocol == nullptr)
        {
            _protocol = protocol::create(this, _buffer);
        }
        _protocol->input_read(_buffer);

        // read next data
        data_read();

        } catch (const exception& e)
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
void input_connexion::data_read()
{
    if (!_alive) return;
    _socket.async_read_some(boost::asio::buffer(_buffer.address(), _buffer.capacity()),
    boost::bind(&input_connexion::socket_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
}

void input_connexion::data_send(const char* data, int data_size)
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
const input_connexion::buffer_type& input_connexion::buffer() const { return _buffer; }
const string& input_connexion::ip_client() const { return _ip_client; }
const string& input_connexion::ip_local() const { return _ip_local; }

