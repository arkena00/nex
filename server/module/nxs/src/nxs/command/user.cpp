#include <nxs/command.hpp>
#include <nxs/core.hpp>
#include <nxs/network/request.hpp>
#include <nxs/user.hpp>
#include <nxs/database.hpp>

namespace nxs
{
    template<>
    struct commands<command::user>
    {
        static void add(nxs::nex& nex)
        {
            user::add(nex.input().param("name").value(), nex.input().param("pass").value());
            nex.output().add("user add");
        }

        static void get(nxs::nex& nex)
        {
            std::stringstream ss;
            for (auto& item : user::get())
            {
                ss << "<br /> - " << item[db::nex.user.name];
            }
            nex.output().add(ss.str());
        }

        static void login(nxs::nex& nex)
        {
            nex.user().login(nex.input().param("name").value(), nex.input().param("pass").value());
            if (nex.user().is_logged())
            {
                nex.output().add("logged as " + nex.user().name());
                return;
            }
            nex.output().add("user login error");
        }
    };

    template<>
    void command::initialize<command::user>()
    {
        command& user_add = command::add("nxs", "user_add", &commands<command::user>::add);
        user_add.param_add("name", param::require, "", "[a-z0-9_]{3,}");
        user_add.param_add("pass", param::require, "", "[a-z]{8,}");

        command::add("nxs", "user_get", &commands<command::user>::get);

        command::add("nxs", "user_login", &commands<command::user>::login);
    }
} // nxs
