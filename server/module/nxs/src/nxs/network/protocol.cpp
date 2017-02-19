#include <nxs/network/protocol.hpp>
#include <nxs/network/protocol/nex.hpp>
#include <nxs/network/protocol/http.hpp>
#include <nxs/network/protocol/ws.hpp>
#include <nxs/network/connexion.hpp>
#include <nxs/core.hpp>
#include <nxs/error.hpp>
#include <string.h>

namespace nxs{namespace network
{
    protocol::protocol(network::connexion* cnx) :
        _connexion(cnx)
    { _input.finish(true); }

    protocol::~protocol() {}

    void protocol::process()
    {
        // input connexion
        if (connexion().iotype() == connexion::input)
        {
            nxs::execute(*this);
            // send output
            if (input().is_finished() || input().data_complete()) { send(_output); }
        }
    }

    void protocol::error_send(const std::string& message)
    {
        if (connexion().iotype() == connexion::input)
        {
            _input.clear();
            _input.finish(true);
            _output.set("nxs::error;");
            _output.add(message);
            send(_output);
        }
        else nxs_error << message << log::network;
    }

    user& protocol::user() { return _user; }
    request& protocol::input() { return _input; }
    request& protocol::output() { return _output; }

    network::connexion& protocol::connexion()
    {
        if (_connexion == nullptr) nxs_error;
        return *_connexion;
    }

    void protocol::input_complete(bool n) { _input._data_complete = n; }

    // create specified protocol
    protocol* protocol::create(network::connexion* cnx, protocol::type protocol_type)
    {
        if (protocol_type == protocol::nex) return create<network::nex>(cnx);
        if (protocol_type == protocol::http) return create<network::http>(cnx);
        if (protocol_type == protocol::ws) return create<network::ws>(cnx);

        nxs_error << "protocol unknown" << log::network;
        return nullptr;
    }

    // create protocol from buffer data
    protocol* protocol::create(network::connexion* cnx, const buffer_type& buf)
    {
        // nex
        if (strncmp(buf.data(), "NEX", 3) == 0) return create<network::nex>(cnx);

        // http
        if (strncmp(buf.data(), "GET", 3) == 0 || strncmp(buf.data(), "POST", 4) == 0)
        {
            // ws
            std::string str_data = std::string(buf.data(), buf.size());
            if (str_data.find("Sec-WebSocket-Key:") != std::string::npos) return create<network::ws>(cnx);
            return create<network::http>(cnx);
        }

        // no protocol found, disconnect
        nxs_error << "protocol_unknown\n" << std::string(buf.data(), buf.size());

        return nullptr;
    }
}} // nxs::network
