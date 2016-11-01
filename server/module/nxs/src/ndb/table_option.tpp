#include <ndb/error.hpp>

namespace ndb
{
    template<class Engine>
    table_option<Engine>::table_option() :
        _parent(nullptr),
        _array(false)
    {}

    template<class Engine>
    table_option<Engine>::table_option(const table<Engine>& parent, bool array) :
        _parent(&parent),
        _array(array)
    {}

    template<class Engine>
    const std::vector<field_base<Engine>>& table_option<Engine>::unique() const { return _unique; }

    template<class Engine>
    void table_option<Engine>::parent_add(const table<Engine>& parent) { _parent  = &parent; }

    template<class Engine>
    bool table_option<Engine>::has_parent() const
    {
        if (_parent == nullptr) return false;
        return true;
    }

    template<class Engine>
    const table<Engine>& table_option<Engine>::parent() const
    {
        if (_parent == nullptr) ndb_error("link table does not exist");
        return *_parent;
    }

    template<class Engine>
    bool table_option<Engine>::is_field() const { return _parent == nullptr ? false : true; }

    template<class Engine>
    bool table_option<Engine>::is_field_array() const { return is_field() && _array ? true : false; }

    template<class Engine>
    bool table_option<Engine>::is_field_single() const { return is_field() && !_array ? true : false; }

    template<class Engine>
    void table_option<Engine>::unique(const table<Engine>& t, std::initializer_list<field_base<Engine>> f)
    {
        if (t.option().is_field()) return;

        table_option<Engine> opt;
        opt._unique = std::vector<field_base<Engine>>(f);
        t.model().table_option_add(opt, "unique");
    }
} // ndb
