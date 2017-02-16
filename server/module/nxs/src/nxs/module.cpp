#include <nxs/module.hpp>

namespace nxs
{
    const std::string module::name_ = "module";
    const std::string module::ext_ = "";
    const db::tables::module& module::db_ref = db::nex.module;

    module::module(int id) : common_module(id) {}
    module::module(const db::line& data) : common_module(data) {}
    //module::module(const std::string& name) : common_module(name) {}
} //nxs
