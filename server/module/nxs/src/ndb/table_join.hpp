#ifndef TABLE_JOIN_H_NDB
#define TABLE_JOIN_H_NDB

#include <ndb/engine/setup.hpp>
#include <string>

namespace ndb
{
    template<class Engine> class field_base;

    template<class Engine = setup<>::engine>
    class table_join
    {
    private:
        std::string _table1;
        std::string _table2;

    public:
        table_join(const std::string& table1, const std::string& table2) :
            _table1(table1),
            _table2(table2)
        {}

        const std::string& table1() const { return _table1; }
        const std::string& table2() const { return _table2; }
    };
} // ndb

#endif // TABLE_JOIN_H_NDB
