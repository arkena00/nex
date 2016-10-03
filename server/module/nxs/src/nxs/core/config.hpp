#ifndef CORE_CONFIG_HPP_NXS
#define CORE_CONFIG_HPP_NXS

#include <string>

namespace nxs
{
    class config
    {
    private:
        config() = default;

    public:
        static std::string network_server_name;
        static std::string network_download_path;
        static size_t network_data_memory_max;

        static void load(const std::string& file);
    };
} // nxs


#endif // CORE_CONFIG_HPP_NXS
