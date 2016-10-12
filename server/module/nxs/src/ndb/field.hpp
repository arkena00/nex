#ifndef FIELD_H_NDB
#define FIELD_H_NDB

#include <ndb/field_base.hpp>
#include <ndb/type.hpp>
#include <ndb/table.hpp>

namespace ndb
{
    template<class Engine> class expression;
    template<class Engine> class query;

    template<class T>
    using Field_Table = typename std::enable_if_t<std::is_base_of<ndb::table<>, T>::value>;

    template<class T, size_t Size = 0, class Engine = setup<>::engine, typename Field_Basic = void>
    class field : public field_base<Engine>
    {
    private:
        T _default_value;

    public:
        using type = T;

        field(const ndb::table<Engine>& table);
        field(const ndb::table<Engine>& table, const std::string& name, const T& default_value = T{});
        field(const ndb::table<Engine>& table, const std::string& name, const field_option<Engine>& option);

        T default_value() const;

        operator expression<Engine>() const;
        template<class V> expression<Engine> operator,(const V& other) const;
        template<class V> expression<Engine> operator=(const V& other) const;
        template<class V> expression<Engine> operator==(const V& other) const;
    };

    // specialize for array field
    template<class T, class Engine>
    class field<T, 0, Engine, Field_Table<T>> : public T
    {
    public:
        field(const ndb::table<Engine>& table) :
            T(table.model(), table_option<Engine>{ table, true })
        {}
    };
    // specialize for single value field
    template<class T, class Engine>
    class field<T, 1, Engine, Field_Table<T>> : public T
    {
    public:
        field(const ndb::table<Engine>& table) :
            T(table.model(), table_option<Engine>{ table, false })
        {}
    };
} // ndb

#include "field.tpp"

#endif // FIELD_H_NDB
