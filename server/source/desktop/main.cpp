#include <nxs.hpp>
#include <nxs/network/server.hpp>
#include <nxs/network/client.hpp>
#include <nxs/network/protocol/http.hpp>

#include <thread>
#include <iostream>

int main()
{
    try {
    nxs::load();
    nxs::network::client client;
    nxs::network::server server(50);

    std::thread server_thread(&nxs::network::server::run, &server);
    std::thread client_thread(&nxs::network::client::run, &client);
    //client_thread.detach();

    /*
    nxs::network::output_connexion& http = client.connexion_add<nxs::network::http>();
    http.connect("37.59.107.118", 80, 0);
    http.on_connect([&](){
                       std::string req = "GET / HTTP/1.1\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\nHost: www.neuroshok.com\r\n\r\n";
                        http.send(req.c_str(), req.size());
                    });

    http.on_read([&](nxs::network::connexion::buffer_type& b) {
                       http.protocol().read();
                       //if (http.protocol().transfer_complete()) std::cout << http.protocol().input().data(0).get();
                    });


    nxs::network::output_connexion& nex_cnx = client.connexion_add<nxs::network::nex>();
    nex_cnx.connect("127.0.0.1", 5050, 0);
    nex_cnx.on_connect([&]() {
                        nex_cnx.protocol().send(nxs::request("nxs::version;"));
                    });

    nex_cnx.on_read([&](nxs::network::connexion::buffer_type& b) {
                       nex_cnx.protocol().read();
                       if (nex_cnx.protocol().transfer_complete()) std::cout << nex_cnx.protocol().input().data(0).get();
                    });


                    */
    client_thread.join();
    server_thread.join();



    } catch (const std::exception& e)
    {
        std::cout << "Fatal server error !! FATALITY !! : " << e.what() << std::endl;
        system("pause");
    }
    std::cout << std::endl << std::endl;

    return 0;
}
