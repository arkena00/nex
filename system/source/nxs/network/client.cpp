#include <nxs/network/client.hpp>
#include <nxs/network/protocol/http.hpp>

namespace nxs{namespace network
{
    // explicit instanciation for users
    template class connexion_manager<output_connexion>;
    template class basic_protocol<io::output>;
    template class basic_output_connexion<nex<io::output>>;
    template class basic_output_connexion<http<io::output>>;

    void client::run()
    {
        ios().run();
    }
}} // nxs::network
