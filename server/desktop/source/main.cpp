#include <nxs/database.hpp>
#include <nxs/core.hpp>
#include <nxs/network/server.hpp>

#include <thread>
#include <iostream>



int main()
{
    try
    {
        nxs::core nxc;
        std::cout << "\n" << nxc.version();

        nxs::network::server server{ 50 };

        server.run();

        /*
        nxs::load();
        nxs::network::client client;
        nxs::network::server server(50);

        server.run();
*/


    } catch (const std::exception &e)
    {
        std::cout << "Fatal server error !! FATALITY !! : " << e.what() << std::endl;
        system("pause");
    }
    std::cout << std::endl << std::endl;

    return 0;
}
