#ifndef ENGINE_SQL_SQL_H_NDB
#define ENGINE_SQL_SQL_H_NDB

#include <ndb/engine/engine.hpp>
#include <ndb/engine/sql/sqlite3.h>

namespace ndb
{
    class sql : public engine<sql>
    {
    private:
        sqlite3* _db;

    public:
        sql(const std::string& identifier);

        virtual bool connect();
        virtual void close();
        virtual ndb::result<sql> exec(ndb::query<sql>& q) const;
        virtual ndb::result<sql> exec(const typename setup<sql>::expression_type& q) const;
    };
} // db

#endif // ENGINE_SQL_SQL_H_NDB

