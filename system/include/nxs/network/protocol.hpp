#ifndef NETWORK_PROTOCOL_H_NXS
#define NETWORK_PROTOCOL_H_NXS

#include <nxs/nex.hpp>
#include <nxs/network/io.hpp>
#include <memory>
#include <functional>

namespace nxs
{
    class user;
    class request;
} // nxs

namespace nxs{namespace network
{
    class connexion;

    class protocol : public nxs::nex
    {
    public:
        virtual ~protocol() = default;

        virtual void read() = 0;
        virtual void send() = 0;
        virtual void send(request&, std::function<void(nxs::nex&)>) = 0;
        virtual void send(const std::string&, std::function<void(nxs::nex&)>) = 0;

        virtual bool transfer_complete() const = 0;
        virtual void transfer_complete(bool n) = 0;
        virtual bool process_complete() const = 0;
        virtual void process_complete(bool n) = 0;
        virtual network::connexion& connexion() = 0;

        template<class Protocol>
        static std::unique_ptr<protocol> create(network::connexion& cnx);
    };
}} // nxs::network

#include "protocol.tcc"

#endif // NETWORK_PROTOCOL_H_NXS
