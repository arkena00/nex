#ifndef ENGINE_SQL_VALUE_H_NDB
#define ENGINE_SQL_VALUE_H_NDB

#include <ndb/engine/sql/type.hpp>
#include <iostream>
namespace ndb
{
    template<class> class value;

    template<>
    class value<sql>
    {
        union value_data
        {
            int as_int;
            double as_double;
            std::string* as_string;

            explicit value_data(int v) : as_int(v) {}
            explicit value_data(double v) : as_double(v) {}
            explicit value_data(const std::string& v) : as_string(new std::string(v)) {}
        };

    private:
        int _type;
        value_data _data;

    public:
        value(const value& other) : _type(other._type), _data(other._data)
        {
            if (_type == SQLITE3_TEXT) _data.as_string = new std::string(other.as_string());
        }
        value& operator=(const value&) = delete;

        explicit value(int v) : _type(SQLITE_INTEGER), _data(v) {}
        explicit value(double v) : _type(SQLITE_FLOAT), _data(v) {}
        explicit value(const std::string& v) : _type(SQLITE3_TEXT), _data(v) {}
        explicit value(const char* v) : _type(SQLITE3_TEXT), _data(v) {}

        template<class T>
        explicit value(const T& v) : _type(ndb::type<sql>::id<T>()), _data(ndb::type<sql>::encode(v)) {}

        ~value()
        {
            if (_type == SQLITE3_TEXT)
            {
                delete _data.as_string;
                _data.as_string = nullptr;
            }
        }

        int type() const { return _type; }
        int as_int() const { return _data.as_int; }
        double as_double() const { return _data.as_double; }
        const std::string& as_string() const { return *_data.as_string; }
    };
} // ndb

#endif // ENGINE_SQL_VALUE_H_NDB
