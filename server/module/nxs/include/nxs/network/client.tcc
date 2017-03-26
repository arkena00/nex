#include <nxs/network/connexion/basic_output.hpp>

namespace nxs{namespace network
{
    template<template<io::type> class Protocol>
    output_connexion& client::connexion_add()
    {
        auto cnx = std::make_unique<basic_output_connexion<Protocol<io::output>>>(*this);
        size_t id = cnx.get()->id();
        connexion_manager::store(std::move(cnx));
        return connexion_manager::connexion(id);
    }
}} // nxs::network
