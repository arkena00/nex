#ifndef NETWORK_PROTOCOL_BASIC_H_NXS
#define NETWORK_PROTOCOL_BASIC_H_NXS

#include <nxs/setup/connexion.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/network/connexion/basic.hpp>
#include <nxs/network/request.hpp>
#include <nxs/user.hpp>

namespace nxs{namespace network
{
    template<size_t> class buffer;

    template<io::type IO_Type>
    class NXS_SHARED basic_protocol : public protocol
    {
     private:
        network::connexion& _connexion;
        bool _transfer_complete;
        bool _process_complete;

        nxs::user _user;
        request _input;
        request _output;

    public:
        using buffer_type = buffer<setup<network::connexion>::buffer_size>;

        basic_protocol(network::connexion& cnx);
        virtual ~basic_protocol();

        bool transfer_complete() const;
        void transfer_complete(bool n);
        bool process_complete() const;
        void process_complete(bool n);

        virtual void read() = 0;
        virtual void send(const request&) = 0;

        virtual void process();
        virtual void error(const std::string& message);

        nxs::user& user() override;
        request& input() override;
        request& output() override;
        network::connexion& connexion();

        template<class Protocol>
        static protocol* create(basic_connexion<io::input>* cnx)
        {
            return static_cast<basic_protocol<IO_Type>*>(new Protocol(cnx));
        }
    };

    template<> void basic_protocol<io::input>::process();
    template<> void basic_protocol<io::input>::error(const std::string& message);
}} // nxs::network

#include "basic.tpp"

#endif // NETWORK_PROTOCOL_BASIC_H_NXS
