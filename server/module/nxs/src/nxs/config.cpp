#include <nxs/config.hpp>
#include <nxs/log.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace nxs
{
    std::string config::network_server_name;
    std::string config::network_download_path;
    size_t config::network_data_memory_max;

    void config::load(const std::string& file)
    {
        using boost::property_tree::ptree;
        ptree pt;
        try {
        read_xml(file, pt);
        } catch (const std::exception& e) { nxs_log << e.what() << log::system; }

        // network
        network_server_name = pt.get("network.server.name", "nex");
        network_download_path = pt.get("network.download_path", "./download/");
        network_data_memory_max = pt.get("network.data_memory_max", 4096 * 4096);
    }
} // nxs
