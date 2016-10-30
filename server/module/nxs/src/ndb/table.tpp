#include <ndb/model.hpp>

namespace ndb
{
    template<class Engine>
    table<Engine>::table(ndb::model<>& model, const std::string& name, const ndb::table_option<Engine>& option) :
        _model(model),
        _name(name),
        _option(option)
    {
        model.table_add(*this);
    }

    template<class Engine>
    const std::string& table<Engine>::name() const { return _name; }

    template<class Engine>
    ndb::model<Engine>& table<Engine>::model() const { return _model; }

    template<class Engine>
    const ndb::table_option<Engine>& table<Engine>::option() const { return _option; }

    template<class Engine>
    expression<Engine> table<Engine>::all() const { return expression<sql>::all(*this); }
} // ndb
