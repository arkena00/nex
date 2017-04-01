#include <nxs/network/protocol/basic.hpp>

namespace nxs{namespace network
{
    // process input on each read request
    template<>
    void basic_protocol<io::input>::process()
    {
        nxs::execute(*this);
        // send output
        if (process_complete() || transfer_complete())
        {
            send(_output);
        }
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

    // process read data from output connexion when all complete, call the callback if req_id exist
    template<>
    void basic_protocol<io::output>::process()
    {
        // if callback, call it when all complete
        if (process_complete() || transfer_complete())
        {
            // req_id exist
            if (_input.header_exist<headers::req_id>())
            {
                size_t req_id = _input.header_value<headers::req_id>();
                if (_callback.count(req_id) > 0)
                {
                    auto& callback = _callback.at(req_id);
                    callback(*this);
                    _callback.erase(req_id);
                }
            }
        }
    }
}} // nxs::network
