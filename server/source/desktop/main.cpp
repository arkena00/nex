#include <nxs/network/server.hpp>
#include <nxs/network/client.hpp>
#include <nxs/network/protocol/http.hpp>
#include <nxs/network/io.hpp>

#include <thread>
#include <iostream>

using namespace nxs::network;

int main()
{
    try
    {
        nxs::load();
        nxs::network::client client;
        nxs::network::server server(50);

        server.run();

        //std::thread client_thread(&nxs::network::client::run, &client);
        //client_thread.join();

    } catch (const std::exception &e)
    {
        std::cout << "Fatal server error !! FATALITY !! : " << e.what() << std::endl;
        system("pause");
    }
    std::cout << std::endl << std::endl;

    return 0;
}
