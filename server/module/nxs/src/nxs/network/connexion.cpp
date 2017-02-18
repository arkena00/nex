#include <nxs/network/connexion.hpp>
#include <nxs/network/protocol.hpp>

namespace nxs{namespace network
{
    connexion::connexion(network::protocol* p) : _protocol(p)
    {
    }

    connexion::~connexion()
    {
        if (_protocol != nullptr) delete _protocol;
        _protocol = nullptr;
    }

    void connexion::data_send(const std::string& data)
    {
        data_send(data.c_str(), data.size());
    }

    int connexion::id() const { return _id; }
    int connexion::iotype() const { return _iotype; }
    bool connexion::alive() const { return _alive; }
    protocol& connexion::protocol() const
    {
        if (_protocol == nullptr) nxs_error << log::system;
        return *_protocol;
    }

    void connexion::protocol_set(const buffer_type& buffer)
    {
        _protocol = protocol::create(this, buffer);
    }

    bool connexion::has_protocol() const
    {
        if (_protocol == nullptr) return false;
        return true;
    }
}} // nxs::network
