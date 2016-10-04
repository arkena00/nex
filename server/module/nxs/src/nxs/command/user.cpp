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
            nxs::user::add(nex.input().param("name").value(), nex.input().param("pass").value());
            nex.output().add("user add");
        }
    };

    template<>
    void command::init<command::user>()
    {
        command& user_add = nxs::command::add("nxs", "user_add", &commands<command::user>::add);
        user_add.param_add("name", param::require, "", "[a-z0-9_]{3,}");
        user_add.param_add("pass", param::require, "", "[a-z]{8,}");
    }
} // nxs
