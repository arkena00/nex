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

        iterator begin() { return _line_list.begin(); }
        iterator end() { return _line_list.end(); }

    };
} // ndb

#endif // RESULT_H_NDB

