#include <iostream>
namespace ndb
{
    template<class Engine>
    void line<Engine>::add(const std::string& id, const value<Engine>& v)
    {
        _data.insert(std::make_pair(id, v));
    }

    template<class Engine> template<class F>
    typename F::type line<Engine>::operator[](const F& f)
    {
        if (!_data.count(f.full_name())) throw std::out_of_range("line[" + f.full_name() + "] does not exist");
        return type<sql>::decode<typename F::type>(_data.at(f.full_name()));
    }
} // ndb
