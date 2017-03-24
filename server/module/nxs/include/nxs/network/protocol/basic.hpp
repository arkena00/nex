#ifndef NETWORK_PROTOCOL_BASIC_H_NXS
#define NETWORK_PROTOCOL_BASIC_H_NXS

#include <nxs/setup/connexion.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/network/connexion/basic.hpp>
#include <nxs/network/request.hpp>
#include <nxs/user.hpp>
#include <deque>

namespace nxs{namespace network
{
    template<io::type IO_Type>
    class basic_protocol : public protocol
    {
     private:
        network::connexion& _connexion;
        bool _transfer_complete;
        bool _process_complete;

        nxs::user _user;
        request _input;
        request _output;

        std::map<size_t, std::function<void(nxs::nex&)>> _callback;

    public:
        using buffer_type = buffer<setup<network::connexion>::buffer_size>;

        basic_protocol(network::connexion& cnx);
        virtual ~basic_protocol() = default;

        virtual void read() = 0;
        virtual void send(const request&) = 0;
        void send(request& req, std::function<void(nxs::nex&)>);
        void send(const std::string&, std::function<void(nxs::nex&)>);

        virtual void process();
        virtual void error(const std::string& message);

        bool transfer_complete() const;
        void transfer_complete(bool n);
        bool process_complete() const;
        void process_complete(bool n);

        nxs::user& user() override;
        request& input() override;
        request& output() override;
        network::connexion& connexion() override;
    };

    template<> void basic_protocol<io::input>::process();
    template<> void basic_protocol<io::input>::error(const std::string& message);
}} // nxs::network

#include "basic.tpp"

#endif // NETWORK_PROTOCOL_BASIC_H_NXS
