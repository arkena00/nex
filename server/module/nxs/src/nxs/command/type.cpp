#include <nxs/command.hpp>
#include <nxs/core.hpp>
#include <nxs/network/request.hpp>
#include <nxs/resource/type.hpp>
#include <sstream>

namespace nxs
{
    template<>
    struct commands<command::type>
    {
        static void add(nxs::nex& nex)
        {
            int id = type::add(nex.input().param("name").value());
            nex.output().add("type added : " + std::to_string(id));
        }

        static void get(nxs::nex& nex)
        {
            const auto& r = db::nex.type;
            std::stringstream ss;
            for (nxs::type& item : type::get())
            {
                ss << "<br />" << item.id() << " - " << item.name();
            }
            nex.output().add(ss.str());
        }
    };

    template<>
    void command::initialize<command::type>()
    {
        command& resource_add = command::add("nxs", "type_add", &commands<command::type>::add);
        resource_add.param_add("name", param::require, "", "[a-z0-9_]{3,}");

        command::add("nxs", "type_get", &commands<command::type>::get);
    }
} // nxs
