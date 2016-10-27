#include <ndb/model.hpp>
#include <ndb/table.hpp>
#include <ndb/field.hpp>
#include <ndb/result.hpp>
#include <ndb/engine/sql/sql.hpp>
#include <ndb/engine/sql/type.hpp>

namespace ndb
{
    template<>
    void model<sql>::table_add(const ndb::table<sql>& t)
    {
        // table is a field of array values, create link table
        if (t.option().is_field_array())
        {
            std::string t1 = t.option().parent().name();
            std::string t2 = t.name();

            _data = "\ncreate table `" + t1 + "_" + t2 + "`(" +
            "id integer not null," +
            t2 + "_id integer not null,"
            "primary key (id," + t2 + "_id),"
            "foreign key(id) references " + t1 + "(id) on delete cascade,"
            "foreign key(" + t2 + "_id) references " + t2 + "(id) on delete cascade);" +
            _data;
            return;
        }
        // table is a field of single value
        if (t.option().is_field())
        {
            _data += t.name() + "_id integer,";
            return;
        }

        if (!_data.empty())
        {
            // remove field coma, and close previous table
            _data = _data.substr(0, _data.size() - 1) + ");";
        }

        _data += "\ncreate table `" + t.name() + "`(";
    }

    template<>
    void model<sql>::table_option_add(const table_option<sql>& t, const std::string& name)
    {
        _data += "\n" + name + "(";
        for (auto field : t.unique())
        {
            _data += field.name() + ",";
        }
        _data.resize(_data.size() - 1);
        _data += "),";
    }

    template<>
    void model<sql>::field_add(const field_base<sql>& f)
    {
        if (f.table().option().is_field()) return;

        std::string str_field = "\n" + f.name();
        std::string str_option = "";
        std::string str_default = "";

        switch (f.type_id())
        {
        case SQLITE_INTEGER:
            str_default = std::to_string(static_cast<const field<type<sql>::get<SQLITE_INTEGER>>&>(f).default_value());
            str_field += " integer"; break;

        case SQLITE_FLOAT:
            str_default = std::to_string(static_cast<const field<type<sql>::get<SQLITE_FLOAT>, 0, sql>&>(f).default_value());
            str_field += " float"; break;

        case SQLITE3_TEXT:
            str_default = static_cast<const field<type<sql>::get<SQLITE3_TEXT>, 0, sql>&>(f).default_value();
            if (f.size() > 0) str_field += " varchar";
            else str_field += " text";
            break;
        }

        // field size
        if (f.size() > 0) str_field += "("+ std::to_string(f.size()) +")";
        // field option
        if (f.option().is_primary()) str_option += " primary key";
        if (f.option().is_autoincrement()) str_option += " autoincrement";
        if (f.option().is_not_null()) str_option += " not null";
        if (f.option().is_unique()) str_option += " unique";
        str_field += str_option;
        // default value
        if (!str_default.empty()) str_field += " DEFAULT " + str_default;

        _data += str_field + ",";
    }

    template<>
    std::string model<sql>::str() const { return _data.substr(0, _data.size() - 1) + ");"; }

    template<>
    void model<sql>::make(const ndb::engine<sql>& e) const
    {
        std::string str_query = str();
        size_t start = 0;
        for (size_t i = 0; i != str_query.size(); i++)
        {
            if (str_query.at(i) == ';')
            {
                std::string table_query = str_query.substr(start, i - start + 1);
                e.exec(table_query);
                start = i;
            }
        }
    }
} // ndb
