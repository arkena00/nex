#ifndef TABLE_OPTION_H_NDB
#define TABLE_OPTION_H_NDB

#include <ndb/engine/setup.hpp>

#include <vector>

namespace ndb
{
    template<class Engine> class field_base;

    template<class Engine = setup<>::engine>
    class table_option
    {
    private:
        std::vector<field_base<Engine>> _primary;
        std::vector<field_base<Engine>> _unique;
        const ndb::table<Engine>* _parent;
        bool _array;

    public:
        table_option();
        table_option(const ndb::table<Engine>&, bool array = false);

        const std::vector<field_base<Engine>>& unique() const;

        void parent_add(const ndb::table<Engine>& parent);
        bool is_field() const;
        bool is_field_array() const;
        bool is_field_single() const;
        const ndb::table<Engine>& parent() const;

        static void unique(const table<Engine>&, std::initializer_list<field_base<Engine>> f);
    };
} // ndb

#include "table_option.tpp"

#endif // TABLE_OPTION_H_NDB
