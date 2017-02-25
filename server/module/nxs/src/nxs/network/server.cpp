#include <nxs/network/server.hpp>
#include <nxs/network/connexion/input.hpp>
#include <nxs/core.hpp>
#include <nxs/log.hpp>
#include <iostream>

using boost::asio::ip::tcp;

///FIXME crash when ios().run() never called

namespace nxs{namespace network
{
    server::server(uint16_t port) :
        _port(port),
        _acceptor(ios(), tcp::endpoint(tcp::v4(), port))
    {}

    server::~server()
    {
        _acceptor.cancel();
        _acceptor.close();
    }

    void server::listen()
    {
        // create new connexion
        input_connexion* cnx = new input_connexion(*this);
        _acceptor.async_accept(cnx->socket(), boost::bind(&server::accept, this, cnx, boost::asio::placeholders::error));
    }

    void server::accept(input_connexion* cnx, const boost::system::error_code& status)
    {
        if (!status)
        {
            // manager load connexion
            load(cnx);
        }
        else
        {
            delete cnx;
            nxs_error << "server connexion" << log::network;
        }
        // create new listening socket
        listen();
    }

    void server::run()
    {
        nxs_log << "server started on port" << _port << log::network;
        listen();
        connexion_manager::run();
    }
}} // nxs::network
