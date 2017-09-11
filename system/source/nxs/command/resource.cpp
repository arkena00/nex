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
            size_t source_id = nex.input().param("source_id").value<size_t>();
            nex.output().add(resource::get());
        }

        static void del(nxs::nex& nex)
        {
            size_t id = nex.input().param("id").value<size_t>();
            resource::del(id);
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
        resource_add.param_add("name", param::require, "", "[a-zA-Z0-9_]{3,}");

        command& resource_get = command::add("nxs", "resource_get", &commands<command::resource>::get);
        resource_get.param_add("source_id", param::require, "0");

        command& resource_del = command::add("nxs", "resource_del", &commands<command::resource>::del);
        resource_del.param_add("id", param::require);

        command& resource_type_add = command::add("nxs", "resource_type_add", &commands<command::resource>::type_add);
        resource_type_add.param_add("id", param::require);
        resource_type_add.param_add("type_id", param::require);
    }
} // nxs
