#ifndef LINE_H_NDB
#define LINE_H_NDB

#include <ndb/engine/type.hpp>
#include <map>

namespace ndb
{
    template<class> class result;

    template<class Engine = setup<>::engine>
    class line
    {
        friend class result<Engine>;
    private:
        std::map<std::string, value<Engine>> _data;

    public:
        void add(const std::string& id, const value<Engine>& v);

        template<class F>
        typename F::type get(const F& f, const typename F::type& default_value) const;

        template<class F>
        typename F::type operator[](const F& f) const;
    };
} // ndb

#include "line.tpp"

#endif // LINE_H_NDB

