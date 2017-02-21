#include <nxs/network/protocol/basic.hpp>

namespace nxs{namespace network
{
    // process input request
    template<>
    void basic_protocol<io::input>::process()
    {
        nxs::execute(*this);
        // send output
        if (process_complete() || transfer_complete()) { send(_output); }
    }

    // send error to input connexion
    template<>
    void basic_protocol<io::input>::error(const std::string& message)
    {
        process_complete(true);
        _input.clear();
        _output.set("nxs::error;");
        _output.add(message);
        send(_output);
    }
}} // nxs::network
