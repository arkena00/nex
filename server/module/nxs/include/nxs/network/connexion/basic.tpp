#include <nxs/error.hpp>
#include <nxs/network/protocol.hpp>

namespace nxs{namespace network
{
    template<io::type IO_Type>
    size_t basic_connexion<IO_Type>::id_ = 0;

    template<io::type IO_Type>
    basic_connexion<IO_Type>::basic_connexion(std::unique_ptr<network::protocol> p) :
        _id(++id_),
        _protocol(std::move(p)),
        _alive(0)
    {}

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::send(const std::string& data)
    {
        send(data.c_str(), data.size());
    }

    template<io::type IO_Type> size_t basic_connexion<IO_Type>::id() const { return _id; }
    template<io::type IO_Type> constexpr io::type basic_connexion<IO_Type>::iotype() const { return IO_Type; }
    template<io::type IO_Type> bool basic_connexion<IO_Type>::is_alive() const { return _alive; }
    template<io::type IO_Type> typename basic_connexion<IO_Type>::buffer_type& basic_connexion<IO_Type>::buffer() { return _buffer; }

    template<io::type IO_Type>
    network::protocol& basic_connexion<IO_Type>::protocol()
    {
        if (_protocol.get() == nullptr) nxs_error << log::system;
        return *_protocol.get();
    }

    template<io::type IO_Type>
    template<class Protocol>
    void basic_connexion<IO_Type>::protocol_set()
    {
        auto p = protocol::create<Protocol>(*this);
        _protocol.swap(p);
    }

    template<io::type IO_Type>
    bool basic_connexion<IO_Type>::has_protocol() const
    {
        if (_protocol.get() == nullptr) return false;
        return true;
    }
}} // nxs::network
