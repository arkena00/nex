#include <nxs/error.hpp>
#include <nxs/serialize.hpp>

namespace nxs{namespace network
{
    template<class T> class memory_data;

    template<class T>
    T data::get() const
    {
        auto str = static_cast<const memory_data<std::string>*>(this)->value_const();
        try
        {
            return nxs::unserialize<T>(str);
        }
        catch (const std::exception&)
        {
            return "data unserialize error";
        }
    }
}} // nxs::network