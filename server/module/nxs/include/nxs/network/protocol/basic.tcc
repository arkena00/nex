#include <nxs/core.hpp>

namespace nxs{namespace network
{
    template<io::type IO_Type>
    basic_protocol<IO_Type>::basic_protocol(network::connexion& cnx) :
        _connexion(cnx),
        _transfer_complete(true),
        _process_complete(true)
    {}

    template<io::type IO_Type>
    void basic_protocol<IO_Type>::error(const std::string& message)
    {
        process_complete(true);
        _input.clear();
        _output.set("nxs::error;");
        _output.add(message);
        nxs_log << "protocol error" << message << log::network;
    }

    template<io::type IO_Type> user& basic_protocol<IO_Type>::user() { return _user; }
    template<io::type IO_Type> request& basic_protocol<IO_Type>::input() { return _input; }
    template<io::type IO_Type> request& basic_protocol<IO_Type>::output() { return _output; }

    template<io::type IO_Type>
    network::connexion& basic_protocol<IO_Type>::connexion()
    {
        return _connexion;
    }

    template<io::type IO_Type>
    void basic_protocol<IO_Type>::send(request& req, std::function<void(nxs::nex&)> fn)
    {
        // add req_id to request
        req.header_add<headers::req_id>();
        size_t id = req.header_value<headers::req_id>();
        // link req_id to callback
        _callback[id] = fn;
        send(req);
    }

    template<io::type IO_Type>
    void basic_protocol<IO_Type>::send(const std::string& str_request, std::function<void(nxs::nex&)> fn)
    {
        nxs::request req(str_request);
        send(req, fn);
    }

    template<io::type IO_Type> bool basic_protocol<IO_Type>::transfer_complete() const { return _transfer_complete; }
    template<io::type IO_Type> void basic_protocol<IO_Type>::transfer_complete(bool n) { _transfer_complete = n; }
    template<io::type IO_Type> bool basic_protocol<IO_Type>::process_complete() const { return _process_complete; }
    template<io::type IO_Type> void basic_protocol<IO_Type>::process_complete(bool n) { _process_complete = n; }
}} // nxs::network
