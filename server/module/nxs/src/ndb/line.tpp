#include <iostream>
namespace ndb
{
    template<class Engine>
    void line<Engine>::add(const std::string& id, const value<Engine>& v)
    {
        _data.insert(std::make_pair(id, v));
    }

    template<class Engine> template<class F>
    typename F::type line<Engine>::get(const F& f, const typename F::type& default_value) const
    {
        if (!_data.count(f.real_name())) return default_value;
        return type<sql>::decode<typename F::type>(_data.at(f.real_name()));
    }

    template<class Engine> template<class F>
    typename F::type line<Engine>::operator[](const F& f) const
    {
        if (!_data.count(f.real_name())) return typename F::type{};// throw std::out_of_range("line[" + f.real_name() + "] does not exist");
        return type<sql>::decode<typename F::type>(_data.at(f.real_name()));
    }
} // ndb
