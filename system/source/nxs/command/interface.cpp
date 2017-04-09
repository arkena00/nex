#include <nxs/core.hpp>
#include <nxs/command.hpp>
#include <nxs/network/request.hpp>
#include <nxs/interface.hpp>

namespace nxs
{
    template<>
    struct commands<command::interface>
    {
        static void get(nxs::nex& nex)
        {
            std::string result = "";
            for (const interface& m : interface::get())
            {
                result += "<br />" + std::to_string(m.id()) + " " + m.name() + " " + m.author();
            }
            nex.output().add(std::move(result));
        }

        static void add(nxs::nex& nex)
        {
            std::string result = "";
            const std::string& ext = nex.input().param("ext").value();
            int mid = interface::add(nex.input().param("name").value(), ext);
            if (interface::load(mid, ext)) result = "interface loaded";
            else result = "unable to load interface";
            nex.output().add(std::move(result));
        }
    };

    template<>
    void command::initialize<command::interface>()
    {
        command& add = nxs::command::add("nxs", "interface_add", &nxs::commands<command::interface>::add);
        add.param_add("name", param::require);
        add.param_add("ext", param::require, "dl");
        add.help_set("return nxs version");

        nxs::command::add("nxs", "interface_get", &nxs::commands<command::interface>::get);
    }
} // nxs
