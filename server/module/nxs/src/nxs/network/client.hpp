#ifndef NETWORK_CLIENT_H_NXS
#define NETWORK_CLIENT_H_NXS

#include <nxs/share.hpp>
#include <nxs/network/connexion/manager.hpp>

namespace nxs{namespace network
{
    class output_connexion;

    class NXS_SHARED client : public connexion_manager<output_connexion>
    {
    public:
        client() = default;
        ~client() = default;

        void run() override;

        template<template<io::type> class Protocol>
        output_connexion& connexion_add();
    };
}} // nxs::network

#include "client.tpp"

#endif // NETWORK_CLIENT_H_NXS
