#include <nxs/core.hpp>
#include <nxs/config.hpp>
#include <nxs/command.hpp>
#include <nxs/network/request.hpp>
#include <nxs/utility/file.hpp>
#include <string>

namespace nxs
{
    template<>
    struct commands<command::file>
    {
        static void add(nxs::nex& nex)
        {
            std::string path = nxs::config::network_download_path;
            std::string name = "";
            for (size_t i = 0; i < nex.input().data_count(); i++)
            {
                name = nex.input().param_value("name", i);
                if (name == "") name = "file_" + std::to_string(i);
                nxs::file::rename(nex.input().data(i).name(), name);
            }
            nex.output().add("NXS_TRANSFER_COMPLETE");
        }

        static void get(nxs::nex& nex)
        {
            for (size_t i = 0; i < nex.input().param("path").size(); i++)
            {
                std::string path = nex.input().param_value("path", i);
                nex.output().file_add(path);
            }
        }
    };

    template<>
    void command::initialize<command::file>()
    {
        command& file_add = nxs::command::add("nxs", "file_add", &commands<command::file>::add);
        file_add.wait_transfer(true);
        file_add.header_add<headers::data_target>(headers::data_target::hdd);
        file_add.param_add("name");

        command& file_get = nxs::command::add("nxs", "file_get", &commands<command::file>::get);
        file_get.param_add("path");
    }
} // nxs
