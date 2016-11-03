#ifndef RESULT_H_NDB
#define RESULT_H_NDB

#include <ndb/line.hpp>

namespace ndb
{
    template<class Engine = setup<>::engine>
    class result
    {
        friend Engine;
        using iterator = typename std::vector<line<Engine>>::iterator;

    private:
        std::vector<line<Engine>> _line_list;
        int _add_id;

    public:
        result() : _add_id(0) {}

        void add(const line<Engine>& l)
        {
            _line_list.push_back(l);
        }

        int add_id() const { return _add_id; }

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

