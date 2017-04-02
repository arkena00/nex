#ifndef NETWORK_CONNEXION_H_NXS
#define NETWORK_CONNEXION_H_NXS

#include <nxs/share.hpp>
#include <nxs/setup/connexion.hpp>
#include <memory>

namespace nxs{namespace network
{
    class protocol;
    class data;
    using data_ptr = std::shared_ptr<data>;

    class NXS_SHARED connexion
    {
    public:
        using buffer_type = setup<connexion>::buffer_type;

        virtual ~connexion() = default;

        virtual size_t id() const = 0;
        virtual network::protocol& protocol() = 0;
        virtual buffer_type& buffer() = 0;
        virtual bool is_alive() const = 0;
        virtual void send(const char* data, size_t data_size) = 0;
        virtual void send(network::data_ptr) = 0;
    };
}} // nxs::network

#endif // NETWORK_CONNEXION_H_NXS
