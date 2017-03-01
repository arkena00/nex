#ifndef NETWORK_BUFFER_H_NXS
#define NETWORK_BUFFER_H_NXS

#include <array>

namespace nxs{namespace network
{
    template<size_t S>
    class buffer
    {
    private:
        std::size_t _data_size;
        std::array<char, S> _data;

    public:
        buffer();
        ~buffer() = default;

        std::array<char, S>* address();
        const char* data() const;
        constexpr size_t capacity() const;
        void reserve(size_t n);
        size_t size() const;
    };
}} // nxs::network

#include "buffer.tpp"

#endif // NETWORK_BUFFER_H_NXS
