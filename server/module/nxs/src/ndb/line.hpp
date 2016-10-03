#ifndef LINE_H_NDB
#define LINE_H_NDB

#include <ndb/engine/type.hpp>
#include <map>

namespace ndb
{
    template<class Engine>
    class line
    {
    private:
        std::map<std::string, value<Engine>> _data;

    public:
        void add(const std::string& id, const value<Engine>& v);

        template<class F>
        typename F::type operator[](const F& f);
    };
} // ndb

#include "line.tpp"

#endif // LINE_H_NDB

