#include <iostream>
namespace ndb
{
    template<class Engine>
    int field_base<Engine>::id_ = 0;

    template<class Engine>
    field_base<Engine>::field_base(ndb::table<Engine>& table,
                                   size_t size,
                                   int type_id,
                                   const field_option<Engine>& option) :
        _table(table),
        _id(auto_id()),
        _name("f" + std::to_string(_id)),
        _size(size),
        _type_id(type_id),
        _option(option)
    {
        // field is an entity id
        if (_option.is_id()) _name = table.name() + "_id";

        table.model().field_add(*this);
    }

    template<class Engine> const table<Engine>& field_base<Engine>::table() const { return _table; }
    template<class Engine> const std::string& field_base<Engine>::name() const { return _name; }
    template<class Engine> size_t field_base<Engine>::size() const { return _size; }
    template<class Engine> int field_base<Engine>::type_id() const { return _type_id; }
    template<class Engine> const field_option<Engine>& field_base<Engine>::option() const { return _option; }

    template<class Engine> int field_base<Engine>::auto_id() { return id_++; }

} // ndb
