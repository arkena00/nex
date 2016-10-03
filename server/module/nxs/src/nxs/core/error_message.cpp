#include <nxs/core/error.hpp>
#include <nxs/core/log.hpp>

#define NXSINITERR(NAME) { NAME, #NAME }

using namespace nxs::errc;

std::map<int, std::string> nxs::error_message_ =
{
    NXSINITERR(success),
    { errc::system, "system error"},

    NXSINITERR(connexion),
    NXSINITERR(connexion_unknown),

    NXSINITERR(protocol),
    NXSINITERR(protocol_unknown),
    NXSINITERR(request_invalid),

    NXSINITERR(data_overflow),
    NXSINITERR(data_hdd_read),
    NXSINITERR(data_hdd_write),

    NXSINITERR(dataconnexion_fail),
    NXSINITERR(database_query),

    NXSINITERR(serialize),

    NXSINITERR(resource_denied),
    NXSINITERR(resource_connexion_del),

    NXSINITERR(user_login),
    NXSINITERR(user_exist),
    NXSINITERR(user_get_fail),
    NXSINITERR(group_del),

    NXSINITERR(command_unknown),
    NXSINITERR(command_invalid),
    NXSINITERR(command_denied),
    NXSINITERR(command_param_missing),
    NXSINITERR(command_header_param_missing),

    NXSINITERR(module),
    NXSINITERR(module_unknown),
    NXSINITERR(module_load_fail),

    NXSINITERR(interface),
    NXSINITERR(interface_unknown),
    NXSINITERR(interface_load_fail)
};

#undef NXSINITERR
