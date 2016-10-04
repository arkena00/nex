#include <nxs/network/protocol.hpp>
#include <nxs/network/protocol/nex.hpp>
#include <nxs/network/protocol/http.hpp>
#include <nxs/network/buffer.hpp>
#include <nxs/core.hpp>
#include <nxs/error.hpp>
#include <string.h>

using nxs::network::protocol;
using nxs::network::connexion;
using nxs::request;

namespace nxs{namespace network
{
    protocol::protocol(network::connexion* cnx) :
        _connexion(cnx)
    { _input.finish(true); }

    protocol::~protocol() {}

    void protocol::input_process()
    {
        nxs::execute(*this);
        // send output
        if (_input.is_finished() || _input.data_complete()) { output_send(_output); }
    }

    void protocol::data_send(const char* data, size_t data_size) {}
    void protocol::error_send(const std::string& message)
    {
        _input.clear();
        _input.finish(true);
        _output.set("nxs::error;");
        _output.add(message);
        output_send(_output);
    }

    // create detected protocol
    protocol* protocol::create(network::connexion* cnx, const buffer_type& buf)
    {
        // nex
        if (strncmp(buf.data(), "NEX", 3) == 0) return create<network::nex>(cnx);

        // http
        if (strncmp(buf.data(), "GET", 3) == 0 || strncmp(buf.data(), "POST", 4) == 0)
        {
            return create<http>(cnx);
        }

        // no protocol found, disconnect
        nxs_error(errc::protocol_unknown, std::string(buf.data(), buf.size()));

        return nullptr;
    }

    request& protocol::input() { return _input; }
    request& protocol::output() { return _output; }

    network::connexion& protocol::connexion()
    {
        if (_connexion == nullptr) nxs_error(errc::system);
        return *_connexion;
    }

    void protocol::input_complete(bool n) { _input._data_complete = n; }
}} // nxs::network
