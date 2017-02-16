#ifndef ENGINE_SQL_EXPRESSION_H_NDB
#define ENGINE_SQL_EXPRESSION_H_NDB

#include <ndb/share.hpp>
#include <ndb/utility/trait.hpp>
#include <ndb/engine/sql/value.hpp>
#include <vector>

namespace ndb
{
    template<class> class field_base;
    template<class> class expression;

    template<>
    class NDB_SHARED expression<sql>
    {
        friend class sql;
        friend class query<sql>;

    public:
        enum typec { unknown, add, get, set, del, condition, join };

    private:
        mutable typec _type;

        std::string _table;
        std::string _join;
        std::string _output;
        std::string _output2;

        static std::vector<value<sql>> value_list_;

    public:
        expression() : _type(unknown) {}
        expression(const field_base<sql>& f, typec type);

        void clear();
        const std::string& output() const;
        const std::string& output2() const;
        const std::string& output_join() const;
        void append(const expression& expr);
        std::string native() const;

        template<class V> expression& operator=(const V& v);
        template<class V> expression& operator==(const V& v);
        expression& operator==(const field_base<sql>& v);

        expression& operator,(const expression<sql>& other);
        expression& operator&&(const expression<sql>& other);

        template<class T>
        static void value_add(const T& t);
        static size_t value_index();
        static expression<sql> all(const table<sql>& t);
    };
} // ndb

namespace ndb
{
    template<class T>
    void expression<sql>::value_add(const T& v)
    {
        value_list_.reserve(20);
        value_list_.emplace_back(v);
    }

    template<class V>
    expression<sql>& expression<sql>::operator=(const V& v)
    {
        value_add(v);
        return *this;
    }

    template<class V>
    expression<sql>& expression<sql>::operator==(const V& v)
    {
        _output += " = ?" + std::to_string(expression<sql>::value_index());
        _type = condition;
        value_add(v);
        return *this;
    }

    template<> expression<sql>& expression<sql>::operator==(const query<sql>& v);
} // ndb

#endif // ENGINE_SQL_EXPRESSION_H_NDB
