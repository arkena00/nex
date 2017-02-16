#include <nxs/error.hpp>

namespace nxs{namespace network
{
    template<class T>
    T data::get() const
    {
        if (_target == hdd) return static_cast<const hdd_data*>(this)->get<T>();
        return static_cast<const memory_data*>(this)->get<T>();
    }

    template<class T, nxs::enable_if<std::is_arithmetic<T>::value>...>
    memory_data::memory_data(T v) : data(data::memory)
    {
        std::string a(std::to_string(v));
        add(a.data(), a.size());
    }
}} // nxs::network
