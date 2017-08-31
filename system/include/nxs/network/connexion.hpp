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
        virtual void send(std::shared_ptr<data>, std::function<void()> = nullptr) = 0;

        template<class T> void send_ref(const T&, std::function<void()> = nullptr);
        template<class T> void send_ref(T&, std::function<void()> = nullptr);
        template<class T> void send(T&&, std::function<void()> = nullptr);

        template<class T> void send_ref(T&&, std::function<void()> = nullptr) = delete;
        template<class T> void send(const T&, std::function<void()> = nullptr) = delete;
        template<class T> void send(T&, std::function<void()> = nullptr) = delete;
    };
}} // nxs::network

#include <nxs/network/data/memory.hpp>

namespace nxs{namespace network
{
    template<class T>
    void connexion::send_ref(const T& t, std::function<void()> fn)
    {
        send(make_memory_data(t), fn);
    }

    template<class T>
    void connexion::send_ref(T& t, std::function<void()> fn)
    {
        send(make_memory_data(t), fn);
    }

    template<class T>
    void connexion::send(T&& t, std::function<void()> fn)
    {
        send(make_memory_data(std::move(t)), fn);
    }
}} // nxs::network

#endif // NETWORK_CONNEXION_H_NXS
