#include <nxs.hpp>
#include <nxs/network/server.hpp>

#include <iostream>

int main()
{
    try {
    nxs::load();
    nxs::network::server::start();
    } catch (const std::exception& e)
    {
        std::cout << "Error : " << e.what() << std::endl;
        system("pause");
    }
    std::cout << std::endl << std::endl;

    return 0;
}
