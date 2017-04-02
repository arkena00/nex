//! \file nxs.cpp
#include <nxs/core.hpp>

#include <nxs/config.hpp>
#include <nxs/version.hpp>
#include <nxs/log.hpp>
#include <nxs/network/server.hpp>
#include <nxs/network/request.hpp>
#include <nxs/command.hpp>
#include <nxs/module.hpp>
#include <nxs/interface.hpp>
#include <nxs/database.hpp>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
////////////////////////              LOAD              ////////////////////////
////////////////////////////////////////////////////////////////////////////////
namespace nxs
{
    std::string version() { return nxs_autoversion::FULLVERSION_STRING; }

    // load nxs
    void load()
    {
        header::init();

        std::cout << "Neuroshok - nex server [version " << version() << "]\n\n";
        config::load("nxs.cfg");

        database::init();
        command::init();
        module::init();
        interface::init();
    }

    void execute(nxs::nex& nex)
    {
        if (command::exist(nex.input().full_command_name()))
        {
            command::get(nex.input().full_command_name()).execute(nex);
        }
        else
        {
            // command not registered, call module or interface
            if (nex.input().module_type() == nxs::request::module) nxs::module::execute(nex);
            if (nex.input().module_type() == nxs::request::interface) nxs::interface::execute(nex);
        }
    }
} //nxs
