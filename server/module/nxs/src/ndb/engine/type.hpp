#ifndef ENGINE_TYPE_H_NDB
#define ENGINE_TYPE_H_NDB

#include <cstddef>
#include <ndb/share.hpp>

namespace ndb
{
    template<class Engine> class value;

    template<class Engine>
    struct NDB_SHARED type
    {
        template<class T> static constexpr int id();

        template<int T> struct type_impl;
        template<int T> using get = typename type_impl<T>::type_;

        template<class T> static auto encode(const T&) -> get<id<T>()>;
        template<class T> static T decode(const value<Engine>&);
    };
} // ndb

#endif // ENGINE_TYPE_H_NDB
