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

        virtual void on_read(std::function<void()>) = 0;
        virtual void on_send(std::function<void(const network::data&)>, size_t progress_size = setup<connexion>::output_progress_size) = 0;
        virtual void on_error(std::function<void(const std::string&)>) = 0;

        virtual size_t id() const = 0;
        virtual network::protocol& protocol() = 0;
        virtual buffer_type& buffer() = 0;
        virtual bool is_alive() const = 0;
        virtual void send(network::data_ptr) = 0;

        template<class T> void send(const T&);
    };
}} // nxs::network

#include <nxs/network/data.hpp>

namespace nxs{namespace network
{
    template<class T>
    void connexion::send(const T& t)
    {
        send(memory_data::make(t));
    }
}} // nxs::network

#endif // NETWORK_CONNEXION_H_NXS
