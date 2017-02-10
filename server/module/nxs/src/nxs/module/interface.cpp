//! \file interface.cpp
//! \brief module class
//! \author ads
//! \date 2015-12-06

#include <nxs/module/interface.hpp>

namespace nxs
{
    const std::string interface::name_ = "interface";
    const std::string interface::ext_ = ".ni";

    interface::interface(int id) : common_module(id) {}
    //interface::interface(const std::string& name) : common_module(name) {}

} //nxs
