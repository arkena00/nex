#include <nxs/error.hpp>
#include <nxs/serialize.hpp>
#include <string>
#include <memory>

namespace nxs
{
    template<class T>
    void request::add(network::memory_data<T>&& d)
    {
        _data.push_back(std::make_unique<network::memory_data<T>>(std::move(d)));
    }

    // default function to add data, serialize data
    /*
    template<class T>
    void request::add(T v_data)
    {
        add(nxs::serialize(v_data));
    }*/
} // nxs
