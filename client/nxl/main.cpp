#include <nxs/network/server.hpp>
#include <nxs/network/client.hpp>
#include <nxs/network/protocol/http.hpp>
#include <chrono>

using namespace nxs;
using namespace nxs::network;





int main()
{
    auto s = std::string("NEX:1.0/data_target=8;data_size=1000000;/nxs::file_add;name=test;;");
    auto data = std::string(1000000, 'z');


    try
    {
        nxs::load();
        nxs::network::client client;

        std::thread client_thread(&nxs::network::client::run, &client);

        output_connexion& nex_cnx = client.connexion_add<network::nex>();

        // data to send
        std::string z = "a";

        //nex_cnx.send(z);
        //nex_cnx.send(std::string("aze"));


        nex_cnx.on_connect([&]()
                           {
                               std::cout << "\nconnected to " << nex_cnx.ip() << ":" << nex_cnx.port() << std::endl;

                               std::string cmd;
                                   std::cout << ">";
                                   std::cin >> cmd;
                                   //nxs::request req(cmd);
                                   //nex_cnx.protocol().send(req);
                                   nex_cnx.send_ref(s);
                                   nex_cnx.send_ref(data);
                           });

        nex_cnx.on_read([&]()
                        {
                            std::cout << "\n\n___" << nex_cnx.protocol().input().data().transfer_size();
                            std::cout.write(nex_cnx.buffer().data(), nex_cnx.buffer().size());
                            std::cout << "\n\nread";
                        });


        nex_cnx.on_send([&](const network::data& data)
        {
            std::cout << "\r                                          ";
            std::cout << "\rProgress : " << (int)(data.transfer_progress() * 100) << " %";
            std::cout << " | time elapsed : " << data.transfer_elapsed_time() << " | speed : " << data.transfer_speed() << " Ko / s";

            if (data.transfer_complete())
            {
                std::cout << "\ntransfer complete : " << data.size() << "bytes in " << data.transfer_elapsed_time() << "s " << data.transfer_speed() << " Ko / s\n" << std::endl;
            }
        });


        std::cout << "connecting...";
        //nex_cnx.connect("127.0.0.1", 50, 0);
        nex_cnx.connect("37.59.107.118", 50, 0);

        client_thread.join();


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
        */

    } catch (const std::exception &e)
    {
        std::cout << "Fatal server error !! FATALITY !! : " << e.what() << std::endl;
        system("pause");
    }
    std::cout << std::endl << std::endl;

    return 0;
}
