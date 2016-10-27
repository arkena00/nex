#include <iostream>
namespace ndb
{
    template<class Engine>
    int field_base<Engine>::auto_id = 0;

    template<class Engine>
    field_base<Engine>::field_base(const ndb::table<Engine>& table,
                                   const std::string& name,
                                   size_t size,
                                   int type_id,
                                   const field_option<Engine>& option) :
        _table(table),
        _name(name),
        _real_name(name),
        _full_name(table.name() + "_" + name),
        _size(size),
        _type_id(type_id),
        _option(option)
    {
        // realname for table field
        if (_table.option().is_field_single()) _real_name = _table.name() + "_" + _name;

        table.model().field_add(*this);
    }

    template<class Engine> const table<Engine>& field_base<Engine>::table() const { return _table; }
    template<class Engine> const std::string& field_base<Engine>::name() const { return _name; }
    template<class Engine> const std::string& field_base<Engine>::real_name() const { return _real_name; }
    template<class Engine> const std::string& field_base<Engine>::full_name() const { return _full_name; }
    template<class Engine> size_t field_base<Engine>::size() const { return _size; }
    template<class Engine> int field_base<Engine>::type_id() const { return _type_id; }
    template<class Engine> const field_option<Engine>& field_base<Engine>::option() const { return _option; }

    template<class Engine> std::string field_base<Engine>::auto_name() { return "f" + std::to_string(auto_id++); }
} // ndb
