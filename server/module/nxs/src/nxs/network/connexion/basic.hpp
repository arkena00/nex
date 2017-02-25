#ifndef NETWORK_CONNEXION_BASIC_H_NXS
#define NETWORK_CONNEXION_BASIC_H_NXS

#include <nxs/share.hpp>
#include <nxs/setup/connexion.hpp>
#include <nxs/network/connexion.hpp>
#include <nxs/network/io.hpp>
#include <nxs/network/buffer.hpp>
#include <memory>
#include <string>

namespace nxs{namespace network
{
    template<io::type IO_Type> class basic_protocol;

    template<io::type IO_Type>
    class NXS_SHARED basic_connexion : public connexion
    {
    public:
        using buffer_type = setup<connexion>::buffer_type;

    private:
        static size_t id_;

        size_t _id;
        std::unique_ptr<network::protocol> _protocol;
        buffer_type _buffer;

    protected:
        bool _alive;

        template<class Protocol>
        void protocol_set();

    public:
        basic_connexion(std::unique_ptr<network::protocol> = nullptr);

        virtual ~basic_connexion();
        virtual void load() = 0;
        virtual void read() = 0;
        virtual void send(const char* data, int data_size) = 0;

        void send(const std::string& data);

        size_t id() const;
        constexpr io::type iotype() const;
        bool is_alive() const;
        network::protocol& protocol();
        buffer_type& buffer();
        bool has_protocol() const;
    };
}} // nxs::network

#include "basic.tpp"

#endif // NETWORK_CONNEXION_BASE_H_NXS
