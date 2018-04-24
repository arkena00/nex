#include <nxs/core.hpp>
#include <nxs/command.hpp>
#include <nxs/network/request.hpp>
#include <nxs/database.hpp>
#include <sstream>

#include <nxs/network/protocol.hpp>
#include <nxs/network/server.hpp>
#include <nxs/network/client.hpp>
#include <nxs/config.hpp>


using std::move;

namespace nxs
{
    template<>
    struct commands<command::nxs>
    {
        static void version(nxs::nex& nex)
        {
            nex.output().add("test");
        }

        static void info(nxs::nex& nex)
        {
            std::stringstream res;
            std::string br = "\n";
            res << "# nex server info";
            res << br << "server name : " << nxs::config::network_server_name;
            res << br << "download path : " << nxs::config::network_download_path;
            //res << br << "server connexions : " << network::server::connexion_count();

            res << br << br << "# server commands" << br;
            for (auto& it : nxs::command::get())
            {
                const nxs::command& cmd = command::get(it.first);
                res << br << cmd.id() << " - " << cmd.full_command_name() << " | " << cmd.help();
                /*
                res << br << "headers : ";
                for (const auto& h : cmd.header_get())
                {
                    const nxs::header& header = *h.second.get();
                    res << " " << header.name();
                }*/
            }

            nex.output().add(move(res.str()));
        }



    }; // commands

    template<>
    void command::initialize<command::nxs>()
    {
        command& version = nxs::command::add("nxs", "version", &nxs::commands<command::nxs>::version);
        version.help_set("return nxs version");

        nxs::command::add("nxs", "info", &nxs::commands<command::nxs>::info);
        version.help_set("display system info");
    }
} // nxs
