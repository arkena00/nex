#include <nxs/core.hpp>
#include <nxs/command.hpp>
#include <nxs/network/request.hpp>
#include <nxs/module.hpp>

namespace nxs
{
    template<>
    struct commands<command::module>
    {
        static void add(nxs::nex& nex)
        {
            std::string result = "";
            int mid = module::add(nex.input().param("name").value());
            const std::string& ext = nex.input().param("ext").value();
            if (module::load(mid, ext)) result = "module loaded";
            else result = "unable to load module";
            nex.output().add(result);
        }
    };

    template<>
    void command::initialize<command::module>()
    {
        command& add = nxs::command::add("nxs", "module_add", &nxs::commands<command::module>::add);
        add.param_add("name", param::require);
        add.param_add("ext", param::require, "dl");
        add.help_set("return nxs version");
    }
} // nxs
