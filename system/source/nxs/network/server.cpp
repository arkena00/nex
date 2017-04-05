#include <nxs/network/server.hpp>

using boost::asio::ip::tcp;

namespace nxs{namespace network
{
    server::server(uint16_t port) :
        _port(port)
    {}

    void server::listen()
    {
        // create new connexion
        input_connexion* cnx = new input_connexion(this->ios(), _port);

        cnx->accept([this, cnx](const boost::system::error_code& err)
        {
            // accept connexion, load and store
            if (!err)
            {
                cnx->on_close([this, id = cnx->id()]()
                              {
                                  this->connexion_delete(id);}
                );
                auto cnx_ptr = std::unique_ptr<input_connexion>(cnx);
                connexion_manager::store(std::move(cnx_ptr));
                cnx->load();
            }
            else
            {
                delete cnx;
                nxs_error << "server connexion" << log::network;
            }
            // create new listening connexion
            listen();
        });
    }

    void server::run()
    {
        nxs_log << "server started on port" << _port << log::network;
        listen();
        connexion_manager::run();
    }
}} // nxs::network
