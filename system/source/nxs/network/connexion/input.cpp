#include <nxs/network/connexion/input.hpp>
#include <nxs/network/server.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/network/protocol/nex.hpp>
#include <nxs/network/protocol/http.hpp>
#include <nxs/log.hpp>

using boost::asio::ip::tcp;

namespace nxs{namespace network
{
    input_connexion::input_connexion(server& server) :
        basic_connexion(server.ios()),
        _server(server)
    {
    }
    input_connexion::~input_connexion()
    {
        nxs_log << "connexion closed " << ip() << id() << log::network;
    }

    // load connexion
    void input_connexion::load()
    {
        _alive = true;
        // client ip
        //_ip_client = _socket.remote_endpoint().address().to_string();
        //_ip_local = _socket.local_endpoint().address().to_string();

        //nxs::event("connexion_open", "id=" + to_string(_id) + ";ip=" + _ip_client + ";");
        nxs_log << "connexion incoming " << ip() << id() << log::network;
        read();
    }

}} // nxs::network
