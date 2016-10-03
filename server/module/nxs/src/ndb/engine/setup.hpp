#ifndef ENGINE_SETUP_H_NDB
#define ENGINE_SETUP_H_NDB

#include <ndb/setup.hpp>
#include <string>

namespace ndb
{
    class sql;
    class unqlite;

    template<>
    struct setup<> { using engine = sql; };

    template<class Engine = setup<>::engine> class engine;
    template<class Engine = setup<>::engine> class model;
    template<class Engine = setup<>::engine> class table;

    template<>
    struct setup<engine<>>
    {
        constexpr static auto path  = "./database/";
    };

    template<>
    struct setup<sql>
    {
        using expression_type = std::string;
        constexpr static auto path = setup<engine<>>::path;
        constexpr static auto ext = ".sql.db";
    };
} // ndb

#endif // ENGINE_SETUP_H_NDB
