#include <nxs/network/data.hpp>

namespace nxs{namespace network
{
    data::data() :
        _transfer_size(0)
    {}

    size_t data::transfer_size() const
    {
        return _transfer_size;
    }

    void data::transfer_add(size_t n)
    {
        _transfer_size += n;
        if (_transfer_size > size()) _transfer_size = size();
    }

    void data::transfer_set(size_t n)
    {
        _transfer_size = n;
    }

    float data::transfer_progress() const
    {
        return _transfer_size / static_cast<float>(size());
    }

    bool data::transfer_complete() const
    {
        return _transfer_size == size();
    }
}} // nxs::network
