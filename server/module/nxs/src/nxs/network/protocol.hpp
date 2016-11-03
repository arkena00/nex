#ifndef NETWORK_PROTOCOL_H_NXS
#define NETWORK_PROTOCOL_H_NXS

#include <nxs/core.hpp>
#include <nxs/user.hpp>
#include <nxs/network/request.hpp>
#include <nxs/setup/connexion.hpp>

namespace nxs{namespace network
{
    class connexion;
    template<size_t> class buffer;

    class NXS_SHARED protocol : public nxs::nex
    {
        friend class nxs::request;

    private:
        network::connexion* _connexion;
        nxs::user _user;
        request _input;
        request _output;

    public:
        using buffer_type = buffer<setup<network::connexion>::buffer_size>;

        protocol(network::connexion* cnx);
        virtual ~protocol();

        void input_complete(bool n);

        virtual void input_read(const buffer_type&) = 0;
        virtual void input_send(const request&) = 0;
        virtual void output_read(const buffer_type&) = 0;
        virtual void output_send(const request&) = 0;

        virtual void input_process();
        virtual void data_send(const char* data, size_t data_size);
        virtual void error_send(const std::string& message);

        nxs::user& user();
        request& input();
        request& output();
        network::connexion& connexion();

        static protocol* create(network::connexion* cnx, const buffer_type&);
        template<class Protocol>
        static protocol* create(network::connexion* cnx)
        {
            return dynamic_cast<protocol*>(new Protocol(cnx));
        }
    };
}} // nxs::network

#endif // NETWORK_PROTOCOL_H_NXS
