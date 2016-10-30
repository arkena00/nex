#ifndef TABLE_H_NDB
#define TABLE_H_NDB

#include <ndb/engine/setup.hpp>
#include <ndb/table_option.hpp>
#include <ndb/expression.hpp>

namespace ndb
{
    template<class Engine> class field_base;

    template<class Engine>
    class table
    {
    private:
        ndb::model<Engine>& _model;
        std::string _name;
        table_option<Engine> _option;

    public:
        table(ndb::model<>& model, const std::string& name, const table_option<Engine>& option = table_option<Engine>{});

        const std::string& name() const;
        ndb::model<Engine>& model() const;
        const table_option<Engine>& option() const;

        expression<Engine> all() const;
    };
} // ndb

#include "table.tpp"

#endif // TABLE_H_NDB
