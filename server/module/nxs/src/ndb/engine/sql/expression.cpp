#include <ndb/engine/sql/expression.hpp>
#include <ndb/field.hpp>
#include <ndb/table.hpp>
#include <ndb/query.hpp>

namespace ndb
{
    std::vector<value<sql>> expression<sql>::value_list_;

    expression<sql>::expression(const field_base<sql>& f, typec type) :
        _type(type),
        _output(f.full_name())
    {
        _table = f.table().name();

        // join by single value field
        if (f.table().option().is_field_single())
        {
            const std::string& parent_table = f.table().option().parent().name();
            const std::string& join_table = f.table().name();
            _join = " INNER JOIN " + join_table + " ON " + parent_table + "." + join_table + "_id = " + join_table + ".id";
        }

        if (type == get) _output += " AS `" +  _output + "`";

        if (type == set || type == add)
        {
            _output = f.real_name();
            _output2 = "?" + std::to_string(value_index());
        }
    }

    void expression<sql>::clear()
    {
        value_list_.clear();
        *this = expression();
    }

    const std::string& expression<sql>::output() const { return _output; }
    const std::string& expression<sql>::output2() const { return _output2; }
    const std::string& expression<sql>::output_join() const { return _join; }

    void expression<sql>::append(const expression& expr)
    {
        _output += expr.native();
    }

    std::string expression<sql>::native() const
    {
        std::string str_native = "";

        if (_type == typec::get) str_native = "SELECT " + _output + " FROM " + _table + _join;
        else if (_type == typec::add) str_native = "INSERT INTO " + _table + "(" + _output + ") VALUES(" + _output2 + ")";
        else if (_type == typec::set) str_native = "REPLACE INTO " + _table + "(" + _output + ") VALUES(" + _output2 + ")";
        else if (_type == typec::del) str_native = "DELETE FROM " + _table + " WHERE " + _output;
        else if (_type == typec::condition) str_native = " WHERE " + _output;
        else return _output;
        return str_native;
    }

    size_t expression<sql>::value_index() { return value_list_.size() + 1; }

////////////////////////////////////////////////////////////////////////////////
////////////////////////           OPERATORS            ////////////////////////
////////////////////////////////////////////////////////////////////////////////
    expression<sql>& expression<sql>::operator,(const expression<sql>& other)
    {
        _output += "," + other.output();
        _join += other.output_join();
        if (_type == typec::set || _type == typec::add) _output2 += "," + other.output2();
        return *this;
    }

    template<>
    expression<sql>& expression<sql>::operator==(const query<sql>& q)
    {
        _output += " = (" + q.native() + ")";
        return *this;
    }

    expression<sql>& expression<sql>::operator&&(const expression<sql>& other)
    {
        _output = "(" + _output  + " AND " + other.output() + ")";
        return *this;
    }
} // ndb
