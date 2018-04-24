#include <nxs/core.hpp>
#include <nxs/version.hpp>

#include <ndb/initializer.hpp>

namespace nxs
{
    // load nxs
    core::core()
    {
        /*
        header::init();

        database::init();
        command::init();
        module::init();
        interface::init();
         */
    }

    std::string core::version() const
    {
        return nxs_autoversion::fullversion;
    }
} // nxs
