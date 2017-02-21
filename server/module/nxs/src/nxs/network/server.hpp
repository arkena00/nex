#ifndef NETWORK_SERVER_H_NXS
#define NETWORK_SERVER_H_NXS

#ifndef NXS_IMPORTED
    #include <boost/bind.hpp>
    #include <boost/asio.hpp>
#endif

#include <nxs/share.hpp>

namespace nxs{namespace network
{
    class input_connexion;

    class NXS_SHARED server
    {
    private:
        static boost::asio::io_service ios_;
        static std::map<int, input_connexion*> connexion_list_;
        boost::asio::ip::tcp::acceptor _acceptor;

        void listen();
        void input(input_connexion* cnx, const boost::system::error_code& status);
    public:
        server(short port);

        boost::asio::io_service& ios() const;

        static const input_connexion& connexion_get(size_t id);
        static void connexion_close(size_t id);
        static bool connexion_exist(size_t id);
        static size_t connexion_count();

        static void start(short port = 50);
    };
}} // nxs::network

#endif // NETWORK_SERVER_H_NXS
