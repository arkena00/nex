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
        static int id_;
        static int id_field_single_;
        static int id_field_array_;

        ndb::model<Engine>& _model;
        int _id;
        std::string _name;
        table_option<Engine> _option;
        int _gen_field_id;

    public:
        table(ndb::model<>& model, const std::string& name, const table_option<Engine>& option = table_option<Engine>{});

        int id() const;
        const std::string& name() const;
        std::string field_name() const;
        ndb::model<Engine>& model() const;
        const table_option<Engine>& option() const;
        int gen_field_id();

        expression<Engine> all() const;

        static int auto_id(const table_option<Engine>&);
    };
} // ndb

#include "table.tpp"

#endif // TABLE_H_NDB
