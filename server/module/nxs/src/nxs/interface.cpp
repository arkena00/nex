#include <nxs/interface.hpp>

namespace nxs
{
    const std::string interface::name_ = "interface";
    const std::string interface::ext_ = ".ni";

    interface::interface(int id) : common_module(id) {}
    //module::module(const std::string& name) : common_module(name) {}
} //nxs
