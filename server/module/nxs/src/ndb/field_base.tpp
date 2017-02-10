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
        _id(table.gen_field_id()),
        _name(table.name() + "_f" + std::to_string(_id)),
        _real_name(_name),
        _size(size),
        _type_id(type_id),
        _option(option)
    {
        // name for field table
        if (_table.option().is_field_single()) _real_name = _table.field_name() + "_" + _real_name;
        // field is an entity id
        if (_option.is_id())
        {
            _name = table.name() + "_id";
            _real_name = _name;
        }
    }

    template<class Engine> const table<Engine>& field_base<Engine>::table() const { return _table; }
    template<class Engine> const std::string& field_base<Engine>::name() const { return _name; }
    template<class Engine> const std::string& field_base<Engine>::real_name() const { return _real_name; }
    template<class Engine> size_t field_base<Engine>::size() const { return _size; }
    template<class Engine> int field_base<Engine>::type_id() const { return _type_id; }
    template<class Engine> const field_option<Engine>& field_base<Engine>::option() const { return _option; }

    template<class Engine> int field_base<Engine>::auto_id()
    {
        return id_++;
    }

} // ndb
