#include <ndb/engine/sql/type.hpp>
#include <ndb/engine/sql/value.hpp>
#include <iostream>

namespace ndb
{
    template<> template<>
    auto type<sql>::encode(const std::chrono::time_point<std::chrono::system_clock>& v) -> get<id<std::decay<decltype(v)>::type>()>
    {
        auto epoch = v.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::seconds>(epoch);
        return value.count();
    }

    template<> template<>
    int type<sql>::decode(const value<sql>& v) { return v.as_int(); }

    template<> template<>
    const char* type<sql>::decode(const value<sql>& v) { return v.as_string().c_str(); }

    template<> template<>
    std::string type<sql>::decode(const value<sql>& v) { return v.as_string(); }

    template<> template<>
    std::chrono::time_point<std::chrono::system_clock> type<sql>::decode(const value<sql>& v)
    {
        return std::chrono::time_point<std::chrono::system_clock>{};
    }
} // ndb
