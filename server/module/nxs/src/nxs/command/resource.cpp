#include <nxs/command.hpp>
#include <nxs/core.hpp>
#include <nxs/network/request.hpp>
#include <nxs/resource.hpp>
#include <sstream>

namespace nxs
{
    template<>
    struct commands<command::resource>
    {
        static void add(nxs::nex& nex)
        {
            int id = resource::add(nex.input().param("name").value());
            nex.output().add("resource added : " + std::to_string(id));
        }

        static void get(nxs::nex& nex)
        {
            nex.output().add(resource::get());
        }

        static void type_add(nxs::nex& nex)
        {
            int id = nex.input().param("id").value<int>();
            int type_id = nex.input().param("type_id").value<int>();
            resource::type_add(id, type_id);
            nex.output().add("resource type added : " + std::to_string(id));
        }
    };

    template<>
    void command::initialize<command::resource>()
    {
        command& resource_add = command::add("nxs", "resource_add", &commands<command::resource>::add);
        resource_add.param_add("name", param::require, "", "[a-z0-9_]{3,}");

        command::add("nxs", "resource_get", &commands<command::resource>::get);

        command& resource_type_add = command::add("nxs", "resource_type_add", &commands<command::resource>::type_add);
        resource_type_add.param_add("id", param::require);
        resource_type_add.param_add("type_id", param::require);
    }
} // nxs
