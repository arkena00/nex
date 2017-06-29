#include <nxs/core.hpp>
#include <nxs/command.hpp>
#include <nxs/network/request.hpp>
#include <nxs/database.hpp>
#include <nxs/resource.hpp>

#include <sstream>

#include <nxs/network/protocol.hpp>
#include <nxs/network/server.hpp>
#include <nxs/network/client.hpp>
#include <nxs/config.hpp>

#include <stdz/variant.hpp>

namespace nxs
{
    template<>
    struct commands<command::nxs>
    {
        static void version(nxs::nex& nex)
        {
            nex.output().add(nxs::version());
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

            nex.output().add(std::move(res.str()));
        }



        static void test(nxs::nex& nex)
        {
            std::string result = "";

            nex.output().add(std::move(result));
        }

        static void dbtest(nxs::nex& nex)
        {
            std::stringstream res;
            try {

            nxs::resource test(1);

            for (nxs::resource& resource : nxs::resource::get())
            {
                res << "<br />" << resource.id() << " " << " " << resource.name();
                for (auto& rt : resource.type_get())
                {
                    res << "<br />types : " << rt.name();
                }
            }


            } catch (const std::exception& e) { res << e.what(); }

            nex.output().add(std::move(res.str()));
        }

        static void rabbit(nxs::nex& nex)
        {
            std::string out =
        R"(:rabbit::rabbit::rabbit::rabbit::rabbit::rabbit::rabbit::rabbit::rabbit::rabbit::rabbit::rabbit::rabbit::rabbit:)";
            nex.output().add(std::move(out));
        }

    }; // commands

    template<>
    void command::initialize<command::nxs>()
    {
        command& version = nxs::command::add("nxs", "version", &nxs::commands<command::nxs>::version);
        version.help_set("return nxs version");

        nxs::command::add("nxs", "info", &nxs::commands<command::nxs>::info);
        version.help_set("display system info");

        // commands to validate response from output request
        nxs::command::add("nxs", "response", [](nxs::nex&){});
        nxs::command::add("nxs", "error", [](nxs::nex&){});

        command& test = nxs::command::add("nxs", "test", &nxs::commands<command::nxs>::test);
        test.param_add("zeta", param::optional);
        test.help_set("coucou");
        //test.header_add<headers::data_target>(headers::data_target::memory);

        nxs::command::add("nxs", "dbtest", &nxs::commands<command::nxs>::dbtest);
        nxs::command::add("nxs", "rabbit", &nxs::commands<command::nxs>::rabbit);
    }
} // nxs
