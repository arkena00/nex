#include <nxs/core.hpp>
#include <nxs/command.hpp>
#include <nxs/network/request.hpp>
#include <nxs/module.hpp>

namespace nxs
{
    template<>
    struct commands<command::module>
    {
        static void get(nxs::nex& nex)
        {
            std::string result = "";
            for (const module& m : module::get())
            {
                result += "<br />" + std::to_string(m.id()) + " " + m.name() + " " + m.author();
            }
            nex.output().add(std::move(result));
        }

        static void add(nxs::nex& nex)
        {
            std::string result = "";
            const std::string& ext = nex.input().param("ext").value();
            int mid = module::add(nex.input().param("name").value(), ext);
            if (module::load(mid, ext)) result = "module loaded";
            else result = "unable to load module";
            nex.output().add(std::move(result));
        }
    };

    template<>
    void command::initialize<command::module>()
    {
        command& add = nxs::command::add("nxs", "module_add", &nxs::commands<command::module>::add);
        add.param_add("name", param::require);
        add.param_add("ext", param::require, "dl");
        add.help_set("return nxs version");

        nxs::command::add("nxs", "module_get", &nxs::commands<command::module>::get);
    }
} // nxs
