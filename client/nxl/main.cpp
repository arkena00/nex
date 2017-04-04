#include <nxs/network/server.hpp>
#include <nxs/network/client.hpp>
#include <nxs/network/protocol/http.hpp>
#include <chrono>

using namespace nxs;
using namespace nxs::network;


int main()
{
    try
    {
        nxs::load();
        nxs::network::client client;

        std::thread client_thread(&nxs::network::client::run, &client);

        output_connexion& nex_cnx = client.connexion_add<network::nex>();
        nex_cnx.on_connect([&]()
                           {
                               std::cout << "\nconnected";
                           });

        nex_cnx.on_read([&]()
                        {
                            std::cout << "\n\n___";
                            std::cout.write(nex_cnx.buffer().data(), nex_cnx.buffer().size());
                            std::cout << "\n\nread";
                        });


        using clock = std::chrono::high_resolution_clock;
        auto t0 = clock::now();
        auto t1 = clock::now();

         //nex_cnx.connect("127.0.0.1", 50, 0);
        nex_cnx.connect("37.59.107.118", 50, 0);

        nex_cnx.on_send([&](const network::data& data)
        {
            if (data.transfer_size() == 0)
            {
                std::cout << "\nstart___\n";
                t0 = clock::now();
            }

            t1 = clock::now();
            auto d = std::chrono::duration_cast<std::chrono::seconds>(t1 -t0);
            std::cout << "\r                                          ";
            std::cout << "\r_" << (int)(data.transfer_progress() * 100) << " %";
            std::cout << " - speed : " << (float)data.transfer_size() / d.count() / 1000 << "Ko / s";

            if (data.transfer_complete())
            {
                t1 = clock::now();
                auto d = std::chrono::duration_cast<std::chrono::seconds>(t1 - t0);
                std::cout << "\ntransfer complete : " << data.size() << "bytes in " << d.count() << "s " << (float)data.size() / d.count() / 1000 << "Ko / s\n";
            }
        });

        std::string s("NEX:1.0/data_target=8;data_size=1000000;/nxs::file_add;name=test;;");
        auto s2 = std::string(1000000, 'z');
        auto d = memory_data::make(s);
        auto d2 = memory_data::make(s2);

        std::string cmd;
        while (1)
        {
            std::cout << "\n>";
            std::cin >> cmd;
            nxs::request req(cmd);
            //nex_cnx.protocol().send(req);
            nex_cnx.send("NEX:1.0//nxs::version;;");
            //nex_cnx.send(d2);
        }

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
