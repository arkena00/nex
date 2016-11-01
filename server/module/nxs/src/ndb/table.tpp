#include <ndb/model.hpp>

namespace ndb
{
    template<class Engine> int table<Engine>::id_ = 0;
    template<class Engine> int table<Engine>::id_field_single_ = 0;
    template<class Engine> int table<Engine>::id_field_array_ = 0;

    template<class Engine>
    table<Engine>::table(ndb::model<>& model, const std::string& name, const ndb::table_option<Engine>& option) :
        _model(model),
        _id(auto_id(option)),
        _name(name),
        _option(option),
        _gen_field_id(0)
    {
        model.table_add(*this);
    }

    template<class Engine>
    int table<Engine>::id() const { return _id; }

    template<class Engine>
    const std::string& table<Engine>::name() const { return _name; }

    template<class Engine>
    std::string table<Engine>::field_name() const { return option().parent().name() + "_" + name() + std::to_string(id()); }

    template<class Engine>
    ndb::model<Engine>& table<Engine>::model() const { return _model; }

    template<class Engine>
    const ndb::table_option<Engine>& table<Engine>::option() const { return _option; }

    template<class Engine>
    int table<Engine>::gen_field_id() { return _gen_field_id++; }

    template<class Engine>
    expression<Engine> table<Engine>::all() const { return expression<sql>::all(*this); }

    template<class Engine>
    int table<Engine>::auto_id(const table_option<Engine>& option)
    {
        if (option.is_field_single()) return id_field_single_++;
        if (option.is_field_array()) return 99;
        return id_++;
    }
} // ndb
