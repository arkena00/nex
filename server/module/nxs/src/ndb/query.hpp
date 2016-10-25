#ifndef QUERY_H_NDB
#define QUERY_H_NDB

#include <ndb/expression.hpp>
#include <ndb/engine/setup.hpp>

namespace ndb
{
    template<class Engine> class result;

    template<class Engine = setup<>::engine>
    class query
    {
    private:
        expression<Engine> _expression;

        query(const query&) = delete;
        query& operator=(const query&) = delete;

    public:
        query() = default;

        void clear();
        typename setup<Engine>::expression_type native() const;
        ndb::result<Engine> exec();
        ndb::result<Engine> result();

        operator ndb::result<Engine>();

        query& operator<<(const ndb::expression<Engine>& expr);
        query& operator+(auto&& expr);
        query& operator-(ndb::expression<Engine>& expr);

        static ndb::result<Engine> exec(const ndb::expression<Engine>&);
    };
} // nxs::db

#include "query.tpp"

#endif // QUERY_H_NDB

