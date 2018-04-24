#include <nxs/error.hpp>
#include <nxs/serialize.hpp>
#include <string>
#include <memory>

namespace nxs
{
    // default function to add data, serialize data
    template<class T>
    void request::add(T v_data)
    {
        data_add(nxs::serialize(v_data));
    }
} // nxs
