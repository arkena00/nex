#include <nxs/network/connexion/input.hpp>
#include <nxs/network/server.hpp>

namespace nxs{namespace network
{
    input_connexion::input_connexion(boost::asio::io_service& ios) :
        basic_connexion(ios)
    {}

    void input_connexion::accept(boost::asio::ip::tcp::acceptor& acceptor, const std::function<void(const boost::system::error_code&)>& fn)
    {
        acceptor.async_accept(_socket, [this, fn](const boost::system::error_code& err)
        {
            fn(err);
        });
    }

    // load connexion
    void input_connexion::load()
    {
        _alive = true;
        //nxs::event("connexion_open", "id=" + to_string(_id) + ";ip=" + _ip_client + ";");
        nxs_log << "connexion incoming " << ip() << id() << log::network;
        read();
    }
}} // nxs::network
