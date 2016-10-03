#ifndef NETWORK_BUFFER_H_NXS
#define NETWORK_BUFFER_H_NXS

#include <array>

namespace nxs{namespace network
{
    template<size_t S>
    class buffer
    {
        friend class input_connexion;

    private:
        std::size_t _data_size;
        std::array<char, S> _data;

        auto address() { return &_data; }

    public:
        buffer() : _data_size(0) {}

        const char* data() const { return _data.data(); }

        constexpr size_t capacity() const { return S; }
        void size(size_t n) { _data_size = n; }
        size_t size() const { return _data_size; }
    };
}} // nxs::network

#endif // NETWORK_BUFFER_H_NXS
