#ifndef NETWORK_CONNEXION_H_NXS
#define NETWORK_CONNEXION_H_NXS

#include <nxs/share.hpp>
#include <nxs/setup/connexion.hpp>
#include <nxs/network/error_code.hpp>
#include <functional>
#include <memory>

namespace nxs{namespace network
{
    class protocol;
    class data;
    using shared_data = std::shared_ptr<data>;

    class NXS_SHARED connexion
    {
    public:
        using buffer_type = setup<connexion>::buffer_type;

        virtual ~connexion() = default;

        virtual void on_read(std::function<void()>) = 0;
        virtual void on_send(std::function<void(const network::data&)>, size_t progress_size = setup<connexion>::output_progress_size) = 0;
        virtual void on_close(std::function<void(const network::error_code&)>) = 0;

        virtual size_t id() const = 0;
        virtual network::protocol& protocol() = 0;
        virtual buffer_type& buffer() = 0;
        virtual std::string ip() const = 0;
        virtual uint16_t port() const = 0;

        virtual bool is_alive() const = 0;
        virtual void send(network::shared_data) = 0;

        template<class T> void send_move(T&&);
        template<class T> void send_move(T&);

        template<class T> void send(T&&);

        template<class T> void send(const T&) = delete;
        template<class T> void send(T&) = delete;
    };
}} // nxs::network

#include <nxs/network/data.hpp>

namespace nxs{namespace network
{
    template<class T>
    void connexion::send_move(T&& t)
    {
        send(make_memory_data(std::move(t)));
    }

    template<class T>
    void connexion::send_move(T& t)
    {
        send_move(std::move(t));
    }

    template<class T>
    void connexion::send(T&& t)
    {
        send_move(std::move(t));
    }
}} // nxs::network

#endif // NETWORK_CONNEXION_H_NXS
