#include <nxs/command.hpp>
#include <nxs/core.hpp>
#include <nxs/network/request.hpp>
#include <nxs/resource.hpp>

namespace nxs
{
    template<>
    struct commands<command::resource>
    {
        static void add(nxs::nex& nex)
        {
            resource::add(nex.input().param("name").value());
            nex.output().add("resource add");
        }

        static void get(nxs::nex& nex)
        {
            const auto& r = db::nex.resource;
            std::stringstream ss;
            for (auto& item : resource::get())
            {
                ss << "<br />" << item[r.id] << " - " << item[r.name];
            }
            nex.output().add(ss.str());
        }
    };

    template<>
    void command::init<command::resource>()
    {
        command& resource_add = command::add("nxs", "resource_add", &commands<command::resource>::add);
        resource_add.param_add("name", param::require, "", "[a-z0-9_]{3,}");

        command::add("nxs", "resource_get", &commands<command::resource>::get);
    }
} // nxs
