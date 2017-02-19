#ifndef NETWORK_CONNEXION_H_NXS
#define NETWORK_CONNEXION_H_NXS

#include <nxs/share.hpp>
#include <nxs/setup/connexion.hpp>
#include <nxs/network/buffer.hpp>
#include <string>

namespace nxs{namespace network
{
    class protocol;

    class NXS_SHARED connexion
    {
    public:
        using buffer_type = setup<connexion>::buffer_type;
        enum iotype_t { input, output };

    private:
        protocol* _protocol;
        buffer_type _buffer;
        iotype_t _iotype;

    protected:
        int _id;
        bool _alive;

    public:
        connexion(iotype_t iotype, protocol* p = nullptr);

        virtual ~connexion();
        virtual void read() = 0;
        virtual void send(const char* data, int data_size) = 0;

        void send(const std::string& data);

        int id() const;
        int iotype() const;
        bool alive() const;
        protocol& protocol() const;
        buffer_type& buffer();
        void protocol_detect(const buffer_type& buffer);
        bool has_protocol() const;
    };
}} // nxs::network

#endif // NETWORK_CONNEXION_H_NXS
