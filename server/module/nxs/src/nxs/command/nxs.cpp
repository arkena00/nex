#include <nxs/core.hpp>
#include <nxs/command.hpp>
#include <nxs/network/request.hpp>
#include <nxs/database.hpp>
#include <nxs/resource.hpp>

#include <sstream>
#include <iostream>

#include <nxs/network/protocol.hpp>
#include <nxs/network/server.hpp>
#include <nxs/network/client.hpp>
#include <nxs/network/connexion/output.hpp>
#include <nxs/config.hpp>

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

            nex.output().add(res.str());
        }



        static void test(nxs::nex& nex)
        {
            nxs::resource r(1);

            std::string zz = nxs::serialize(r);
            std::cout << "\n__" << zz;
            nxs::resource test = nxs::unserialize<nxs::resource>(zz);
            std::cout << "____________" << test.name() <<" : "<< test.id();

            nex.output().add(r);

            //nex.output().file_add("d:/ads.txt");

            /*
            std::string result = R"__(
            <form enctype="multipart/form-data" action="/nxs::test;;" method="post">
                <input id="file" type="file" />
                <input type = "submit" />
            </form>
            )__";*/

            std::string result = R"__(
            <h1>Projet nex</h1>
            Ce projet a pour but de créer un réseau de données structuré et de fournir des fonctionnalités modulable afin que l'utilisateur puisse gérer depuis une interface client générique et personnalisable toute donnée qu'elle soit local ou réseau.
            <br />
            <br /><img src = 'http://nex.neuroshok.com/image/nex_presentation.jpg' />
            )__";
            nex.output().add(result);
        }

        static void dbtest(nxs::nex& nex)
        {
            std::stringstream res;
            try {
            const auto& t = db::nex.type;
            const auto& r = db::nex.resource;
            const auto& u = db::nex.user;


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

            nex.output().add(res.str());
        }
    };

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
    }
} // nxs
