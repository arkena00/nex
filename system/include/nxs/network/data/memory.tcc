#include <nxs/network/data.hpp>

namespace nxs{namespace network
{
    template<class T>
    memory_data<T>::memory_data() {}


    template<class T>
    memory_data<T>::memory_data(const T& t) : _data(t) {}

    template<class T>
    memory_data<T>::memory_data(T& t) : _data(t) {}

    template<class T>
    memory_data<T>::memory_data(T&& t) : _data(std::move(t)) {}

    template<class T>
    void memory_data<T>::add(const char* data_ptr, size_t data_size)
    {
        _data.insert(_data.end(), data_ptr, data_ptr);
    }

    template<class T>
    const char* memory_data<T>::ptr()
    {
        return _data.data();
    }

    template<class T>
    size_t memory_data<T>::size() const
    {
        return _data.size();
    }

    template<class T>
    void memory_data<T>::reserve(size_t n)
    {
        _data.reserve(n);
    }

    template<class T>
    data::target_code memory_data<T>::target() const
    {
        return data::memory;
    }

    template<class T>
    network::shared_data make_memory_data(T&& v)
    {
        return std::make_shared<memory_data<T>>(std::move(v));
    }
}} // nxs::network
