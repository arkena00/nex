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
    private:
        network::connexion* _connexion;
        nxs::user _user;
        request _input;
        request _output;

    public:
        enum type { nex, http, ws };
        using buffer_type = buffer<setup<network::connexion>::buffer_size>;

        protocol(network::connexion* cnx);
        virtual ~protocol();

        void input_complete(bool n);

        virtual void read() = 0;
        virtual void send(const request&) = 0;

        virtual void process();
        virtual void error_send(const std::string& message);

        nxs::user& user();
        request& input();
        request& output();
        network::connexion& connexion();

        static protocol* create(network::connexion* cnx, type protocol_type);
        static protocol* create(network::connexion* cnx, const buffer_type&);
        template<class Protocol>
        static protocol* create(network::connexion* cnx);
    };
}} // nxs::network

namespace nxs{namespace network
{
    template<class Protocol>
    protocol* protocol::create(network::connexion* cnx)
    {
        return dynamic_cast<protocol*>(new Protocol(cnx));
    }
}} // nxs::network

#endif // NETWORK_PROTOCOL_H_NXS
