#include <nxs/error.hpp>
#include <nxs/serialize.hpp>

namespace nxs{namespace network
{
    template<class T>
    T data::get() const
    {

        return std::string("test");
        //if (_target == hdd) return static_cast<const hdd_data*>(this)->get<T>();
        //return static_cast<const memory_data*>(this)->get<T>();
    }
}} // nxs::network