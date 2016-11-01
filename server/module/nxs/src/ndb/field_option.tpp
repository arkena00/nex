#include <ndb/error.hpp>

namespace ndb
{
    template<class Engine>
    field_option<Engine>::field_option() :
        _id(false),
        _primary(false),
        _autoincrement(false),
        _unique(false),
        _null(true)
    {}

    template<class Engine>
    field_option<Engine>::field_option(int c) : field_option()
    {
        if (c & primary) _primary = true;
        if (c & autoincrement) _autoincrement = true;
        if (c & unique) _unique = true;
        if (c & not_null) _null = false;
    }

    template<class Engine> bool field_option<Engine>::is_id() const { return _id; }
    template<class Engine> bool field_option<Engine>::is_primary() const { return _primary; }
    template<class Engine> bool field_option<Engine>::is_autoincrement() const { return _autoincrement; }
    template<class Engine> bool field_option<Engine>::is_unique() const { return _unique; }
    template<class Engine> bool field_option<Engine>::is_null() const { return _null; }
    template<class Engine> bool field_option<Engine>::is_not_null() const { return !_null; }

    template<class Engine>
    field_option<Engine> field_option<Engine>::id()
    {
        field_option f;
        f._id = true;
        f._primary = true;
        f._autoincrement = true;
        f._null = false;
        return f;
    }
} // ndb
