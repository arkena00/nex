#ifndef ENGINE_SQL_TYPE_H_NDB
#define ENGINE_SQL_TYPE_H_NDB

#include <ndb/engine/type.hpp>
#include <ndb/engine/sql/sqlite3.h>
#include <chrono>
#include <string>

namespace ndb
{
    class sql;
    // associate cpp type to engine native type
    template<> template<> constexpr int type<sql>::id<int>() { return SQLITE_INTEGER; }
    template<> template<> constexpr int type<sql>::id<double>() { return SQLITE_FLOAT; }
    template<> template<> constexpr int type<sql>::id<std::string>() { return SQLITE3_TEXT; }
    template<> template<> constexpr int type<sql>::id<std::chrono::time_point<std::chrono::system_clock>>() { return SQLITE_INTEGER; }

    // associate engine native type to cpp scalar type
    template<> template<> struct type<sql>::type_impl<SQLITE_INTEGER> { using type_ = int; };
    template<> template<> struct type<sql>::type_impl<SQLITE_FLOAT> { using type_ = double; };
    template<> template<> struct type<sql>::type_impl<SQLITE3_TEXT> { using type_ = std::string; };
} // ndb

namespace ndb
{
    template<> template<>
    NDB_SHARED int type<sql>::decode(const value<sql>& v);
    template<> template<>
    NDB_SHARED std::string type<sql>::decode(const value<sql>& v);
} // ndb

#endif // ENGINE_SQL_TYPE_H_NDB
