#include <nxs/network/client.hpp>
#include <nxs/network/connexion/output.hpp>

#include <nxs/network/protocol/nex.hpp>
#include <nxs/network/protocol/http.hpp>

namespace nxs{namespace network
{
    // explicit instanciation for users
    template class connexion_manager<output_connexion>;
    template class basic_output_connexion<nex<io::output>>;
    template class basic_output_connexion<http<io::output>>;

    void client::run()
    {
        while (true)
        {
            ios().run();
        }
    }
}} // nxs::network
