#ifndef FIELD_OPTION_H_NDB
#define FIELD_OPTION_H_NDB

#include <ndb/engine/setup.hpp>

namespace ndb
{
    template<class Engine = setup<>::engine>
    class field_option
    {
    public: enum code { primary = 1, autoincrement = 2, unique = 4, not_null = 8 };

    private:
        bool _primary;
        bool _autoincrement;
        bool _unique;
        bool _null;

    public:
        field_option();
        field_option(int c);

        bool is_primary() const;
        bool is_autoincrement() const;
        bool is_unique() const;
        bool is_null() const;
        bool is_not_null() const;

        static field_option id();
    };
} // ndb

#include "field_option.tpp"

#endif // FIELD_OPTION_H_NDB
