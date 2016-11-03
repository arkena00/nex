#include <nxs/network/server.hpp>
#include <nxs/core.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <nxs/network/connexion/input.hpp>

boost::asio::io_service nxs::network::server::ios_;

using boost::asio::ip::tcp;
using nxs::network::server;


server::server(short port) : _acceptor(server::ios_, tcp::endpoint(tcp::v4(), port))
{
    nxs_log("server started on port " + std::to_string(port), log::network);
    listen();
}

void server::listen()
{
    // create new connexion
    input_connexion* cnx = input_connexion::create(server::ios_);

    _acceptor.async_accept(cnx->socket(), boost::bind(&server::input, this, cnx, boost::asio::placeholders::error));
}


void server::input(input_connexion* cnx, const boost::system::error_code& status)
{
    if (!status)
    {
        //load cnx
        cnx->load();
    }
    else
    {
        delete cnx;
        nxs_error(errc::connexion);
    }

    //create new listening socket
    listen();
}

void server::start(short port)
{
    network::server server(port);
    ios_.run();
}
