#include <nxs/network/server.hpp>
#include <nxs/core.hpp>
#include <nxs/log.hpp>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <nxs/network/connexion/input.hpp>

using boost::asio::ip::tcp;

namespace nxs{namespace network
{
    boost::asio::io_service server::ios_;
    std::map<int, input_connexion*> server::connexion_list_;

    server::server(short port) : _acceptor(server::ios_, tcp::endpoint(tcp::v4(), port))
    {
        nxs_log << "server started on port" << port << log::network;
        listen();
    }

    void server::listen()
    {
        // create new connexion
        input_connexion* cnx = input_connexion::create(*this);

        _acceptor.async_accept(cnx->socket(), boost::bind(&server::input, this, cnx, boost::asio::placeholders::error));
    }

    void server::input(input_connexion* cnx, const boost::system::error_code& status)
    {
        if (!status)
        {
            cnx->load();
            // store connexion
            server::connexion_list_[cnx->id()] = cnx;
        }
        else
        {
            delete cnx;
            nxs_error << "server connexion" << log::network;
        }
        // create new listening socket
        listen();
    }

    boost::asio::io_service& server::ios() const { return ios_; }

    bool server::connexion_exist(size_t id)
    {
        if (connexion_list_.find(id) != connexion_list_.end()) return true;
        return false;
    }

    const input_connexion& server::connexion_get(size_t id)
    {
        if (connexion_exist(id)) return *connexion_list_.at(id);
        nxs_error << "connexion not found" << id << log::network;
    }

    void server::connexion_close(size_t id)
    {
        if (connexion_exist(id))
        {
            delete connexion_list_.at(id);
            connexion_list_.erase(id);
        }
    }

    size_t server::connexion_count() { return connexion_list_.size(); }

    void server::start(short port)
    {
        network::server server(port);
        ios_.run();
    }
}} // nxs::network
