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
    #ifndef NXS_IMPORTED
        static boost::asio::io_service ios_;
        boost::asio::ip::tcp::acceptor _acceptor;

        void listen();
        void input(input_connexion* cnx, const boost::system::error_code& status);
    #endif
    public:
        server(short port);

        static void start(short port = 50);
    };
}} // nxs::network

#endif // NETWORK_SERVER_H_NXS
