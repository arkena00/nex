#include <ndb/type.hpp>
#include <ndb/expression.hpp>

namespace ndb
{
    template<class Engine> class expression;

    // ctor with default value
    template<class T, size_t Size, class Engine, typename Field_Basic>
    field<T, Size, Engine, Field_Basic>::field(ndb::table<Engine>& table,
                                               const T& default_value) :
        field_base<Engine>(table, Size, ndb::type<Engine>::template id<T>()),
        _default_value(default_value)
    {
        table.model().field_add(*this);
    }

    // ctor with field option
    template<class T, size_t Size, class Engine, typename Field_Basic>
    field<T, Size, Engine, Field_Basic>::field(ndb::table<Engine>& table,
                                               const field_option<Engine>& option) :
        field_base<Engine>(table, Size, ndb::type<Engine>::template id<T>(), option)
    {
        table.model().field_add(*this);
    }

    template<class T, size_t Size, class Engine, typename Field_Basic>
    const T& field<T, Size, Engine, Field_Basic>::default_value() const
    {
        return _default_value;
    }


    template<class T, size_t Size, class Engine, typename Field_Basic>
    field<T, Size, Engine, Field_Basic>::operator expression<Engine>() const
    {
        return expression<Engine>(*this, expression<Engine>::get);
    }

    template<class T, size_t Size, class Engine, typename Field_Basic>
    template<class V>
    expression<Engine> field<T, Size, Engine, Field_Basic>::operator,(const V& other) const
    {
        expression<Engine> test(*this, expression<sql>::get);
        return test , other;
    }

    template<class T, size_t Size, class Engine, typename Field_Basic>
    template<class V>
    expression<Engine> field<T, Size, Engine, Field_Basic>::operator=(const V& other) const
    {
        expression<Engine> test(*this, expression<sql>::set);
        return test = other;
    }

    template<class T, size_t Size, class Engine, typename Field_Basic>
    template<class V>
    expression<Engine> field<T, Size, Engine, Field_Basic>::operator==(const V& other) const
    {
        expression<Engine> test(*this, expression<sql>::condition);
        return test == other;
    }

    template<class T, size_t Size, class Engine, typename Field_Basic>
    expression<Engine> field<T, Size, Engine, Field_Basic>::operator==(const field<int>& other) const
    {
        expression<Engine> test(*this, expression<sql>::join);
        return test == static_cast<field_base<Engine>>(other);
    }
} // ndb

