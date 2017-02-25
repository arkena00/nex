#include <nxs.hpp>
#include <nxs/network/server.hpp>
#include <nxs/network/client.hpp>
#include <nxs/network/connexion/output.hpp>

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
