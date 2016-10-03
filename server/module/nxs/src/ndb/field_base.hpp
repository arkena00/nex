#ifndef FIELD_BASE_H_NDB
#define FIELD_BASE_H_NDB

#include <ndb/engine/setup.hpp>
#include <ndb/field_option.hpp>
#include <cstddef>
#include <string>

namespace ndb
{
    template<class Engine = setup<>::engine>
    class field_base
    {
    private:
        static int auto_id;

        const table<Engine>& _table;
        std::string _name;
        std::string _real_name;
        std::string _full_name;
        size_t _size;
        int _type_id;
        field_option<Engine> _option;

    public:
        field_base(const table<Engine>& table,
                   const std::string& name,
                    size_t size,
                    int type_id,
                    const field_option<Engine>& option = field_option<Engine>{});

        const table<Engine>& table() const;
        const std::string& name() const;
        const std::string& real_name() const;
        const std::string& full_name() const;
        size_t size() const;
        int type_id() const;
        const field_option<Engine>& option() const;

        static std::string auto_name();
    };
} // ndb

#include "field_base.tpp"

#endif // FIELD_BASE_H_NDB
