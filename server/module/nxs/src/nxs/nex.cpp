#include <nxs/nex.hpp>
#include <nxs/network/protocol.hpp>

namespace nxs
{
    network::protocol& nex::protocol() { return static_cast<network::protocol&>(*this); }
} // nxs

