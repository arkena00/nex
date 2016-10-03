#ifndef UTILITY_TRAIT_H_NDB
#define UTILITY_TRAIT_H_NDB

#include <ndb/engine/setup.hpp>

namespace ndb
{
    template<class Engine> class field_base;
    template<class Engine> class query;

    namespace trait
    {
        template<class T> using enable_if_field = std::enable_if_t<std::is_base_of<field_base<setup<>::engine>, T>::value>;
        template<class T> using enable_if_query = std::enable_if_t<std::is_base_of<query<setup<>::engine>, T>::value>;
        template<class T> using enable_if_expression = std::enable_if_t
        <
            !std::is_base_of<field_base<setup<>::engine>, T>::value &&
            !std::is_base_of<query<setup<>::engine>, T>::value
        >;
    } // trait
} // ndb

#endif // UTILITY_TRAIT_H_NDB
