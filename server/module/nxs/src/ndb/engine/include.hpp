#ifdef NDB_ENGINE_SQL
    #ifdef ENGINE_H_NDB
        #include <ndb/engine/sql/sql.hpp>
    #endif
    #ifdef TYPE_H_NDB
        #include <ndb/engine/sql/type.hpp>
    #endif
    #ifdef EXPRESSION_H_NDB
        #include <ndb/engine/sql/expression.hpp>
    #endif

#elif NDB_ENGINE_UNQLITE
    #ifdef EXPRESSION_H_NDB
        #include <ndb/engine/unqlite/expression.hpp>
    #endif

#else
    #error "You have to define a database engine"
#endif
