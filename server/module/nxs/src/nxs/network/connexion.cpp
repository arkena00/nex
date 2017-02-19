#include <nxs/network/connexion.hpp>
#include <nxs/network/protocol.hpp>

namespace nxs{namespace network
{
    connexion::connexion(iotype_t iotype, network::protocol* p) :
        _protocol(p),
        _iotype(iotype)
    {}

    connexion::~connexion()
    {
        if (_protocol != nullptr) delete _protocol;
        _protocol = nullptr;
    }

    void connexion::send(const std::string& data)
    {
        send(data.c_str(), data.size());
    }

    int connexion::id() const { return _id; }
    int connexion::iotype() const { return _iotype; }
    bool connexion::alive() const { return _alive; }
    connexion::buffer_type& connexion::buffer() { return _buffer; }
    protocol& connexion::protocol() const
    {
        if (_protocol == nullptr) nxs_error << log::system;
        return *_protocol;
    }

    void connexion::protocol_detect(const buffer_type& buffer)
    {
        _protocol = protocol::create(this, buffer);
    }

    bool connexion::has_protocol() const
    {
        if (_protocol == nullptr) return false;
        return true;
    }
}} // nxs::network
