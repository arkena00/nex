#include <nxs/interface.hpp>

namespace nxs
{
    const std::string interface::name_ = "interface";
    const std::string interface::ext_ = ".ni";

    interface::interface(int id) : common_module(id) {}
    interface::interface(const db::line& data) : common_module(data) {}
    //module::module(const std::string& name) : common_module(name) {}
} //nxs

