#ifndef RESULT_H_NDB
#define RESULT_H_NDB

#include <ndb/line.hpp>

namespace ndb
{
    template<class Engine = setup<>::engine>
    class result
    {
        using iterator = typename std::vector<line<Engine>>::iterator;

    private:
        std::vector<line<Engine>> _line_list;

    public:
        void add(const line<Engine>& l)
        {
            _line_list.push_back(l);
        }

        size_t size() const { return _line_list.size(); }

        line<Engine>& operator[](int index) { return _line_list.at(index); }

        template<class F>
        typename F::type operator[](const F& f)
        {
            if (!_line_list[0]._data.count(f.real_name())) throw std::out_of_range("line[" + f.real_name() + "] does not exist");
            return type<sql>::decode<typename F::type>(_line_list[0]._data.at(f.real_name()));
        }

        iterator begin() { return _line_list.begin(); }
        iterator end() { return _line_list.end(); }

    };
} // ndb

#endif // RESULT_H_NDB

