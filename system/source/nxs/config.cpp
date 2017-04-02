#include <nxs/config.hpp>
#include <nxs/log.hpp>

namespace nxs
{
    std::string config::network_server_name;
    std::string config::network_download_path;
    size_t config::network_data_memory_max;

    void config::load(const std::string& file)
    {
        // network
        network_server_name = "nex";
        network_download_path = "./download/";
        network_data_memory_max = 4096 * 4096;
    }
} // nxs
