#include <nxs/core.hpp>
#include <nxs/command.hpp>
#include <nxs/network/request.hpp>
#include <nxs/database.hpp>
#include <iostream>
#include <nxs/resource.hpp>

namespace nxs
{
    template<>
    struct commands<command::nxs>
    {
        static void version(nxs::nex& nex)
        {
            nex.output().add(nxs::version());
        }

        static void test(nxs::nex& nex)
        {
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
            const auto& t = db::nex.type;

            db::query q;
            q  << (t.id, t.name, t.image, t.description, t.author);
            std::cout << q.native();

            for (const nxs::type& item : nxs::type::get())
            {
                res << "<br />" << item.name() << " - " << item.author();
            }

            nex.output().add(res.str());
        }
    };

    template<>
    void command::init<command::nxs>()
    {
        command& version = nxs::command::add("nxs", "version", &nxs::commands<command::nxs>::version);
        version.help_set("return nxs version");

        command& test = nxs::command::add("nxs", "test", &nxs::commands<command::nxs>::test);
        test.param_add("zeta", param::optional);
        test.help_set("coucou");
        //test.header_add<headers::data_target>(headers::data_target::memory);

        nxs::command::add("nxs", "dbtest", &nxs::commands<command::nxs>::dbtest);
    }
} // nxs
