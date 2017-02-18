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

    // associate engine native type to cpp type
    template<> struct cpp_type<sql, SQLITE_INTEGER> { using type = int; };
    template<> struct cpp_type<sql, SQLITE_FLOAT> { using type = double; };
    template<> struct cpp_type<sql, SQLITE3_TEXT> { using type = std::string; };

    template<> template<>
    auto type<sql>::encode(const std::chrono::time_point<std::chrono::system_clock>& v) -> get<id<std::decay<decltype(v)>::type>()>;
} // ndb

#endif // ENGINE_SQL_TYPE_H_NDB
