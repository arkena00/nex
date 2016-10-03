//! \file nxs.cpp
//! \brief process requested commands

#include <nxs/core/nxs.hpp>
#include <nxs/core/nex.hpp>
#include <nxs/core/config.hpp>
#include <nxs/core/version.hpp>
#include <nxs/core/log.hpp>
#include <nxs/network/server.hpp>
#include <nxs/network/request.hpp>
#include <nxs/command.hpp>
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

        ndb::engine<>::model_add(ndb::nex);
        ndb::engine<>::connect("nxs");

        command::load();
    }

    void execute(nxs::nex& nex)
    {
        if (command::exist(nex.input().full_command_name()))
        {
            command::get(nex.input().full_command_name()).execute(nex);
        }
    }
} //nxs
