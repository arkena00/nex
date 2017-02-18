#ifndef NETWORK_CONNEXION_H_NXS
#define NETWORK_CONNEXION_H_NXS

#include <nxs/share.hpp>
#include <nxs/setup/connexion.hpp>
#include <string>

namespace nxs{namespace network
{
    class protocol;

    class NXS_SHARED connexion
    {
    private:
        protocol* _protocol;

    protected:
        int _id;
        int _iotype;
        bool _alive;

    public:
        using buffer_type = setup<connexion>::buffer_type;
        enum { input, output };

        connexion(protocol* p = nullptr);

        virtual ~connexion();
        virtual const buffer_type& buffer() const = 0;
        virtual void data_read() = 0;
        virtual void data_send(const char* data, int data_size) = 0;

        void data_send(const std::string& data);

        int id() const;
        int iotype() const;
        bool alive() const;
        protocol& protocol() const;
        void protocol_set(const buffer_type& buffer);
        bool has_protocol() const;
    };
}} // nxs::network

#endif // NETWORK_CONNEXION_H_NXS
