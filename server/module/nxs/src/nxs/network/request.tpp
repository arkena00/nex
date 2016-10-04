#include <nxs/error.hpp>
#include <nxs/network/header.hpp>
#include <string>

namespace nxs
{
    template<class T>
    void request::add(T v_data)
    {
        _data.push_back(std::make_unique<network::memory_data>(v_data));
        header_add<headers::data_size>(_data.back().get()->size());
    }
} // nxs
