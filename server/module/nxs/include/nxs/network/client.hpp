#ifndef NETWORK_CLIENT_H_NXS
#define NETWORK_CLIENT_H_NXS

#include <nxs/share.hpp>
#include <nxs/network/connexion/manager.hpp>

namespace nxs{namespace network
{
    class output_connexion;
    template<io::type> class nex;

    class NXS_SHARED client : public connexion_manager<output_connexion>
    {
    public:
        client() = default;
        ~client() = default;

        void run() override;

        template<template<io::type> class Protocol = nex>
        output_connexion& connexion_add();
    };
}} // nxs::network

#include "client.tcc"

#endif // NETWORK_CLIENT_H_NXS
