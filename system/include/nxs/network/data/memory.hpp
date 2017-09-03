#ifndef NETWORK_DATA_MEMORY_H_NXS
#define NETWORK_DATA_MEMORY_H_NXS

#include <nxs/network/data.hpp>

namespace nxs{namespace network
{
    template<class T>
    class memory_data : public data
    {
    private:
        stdz::variant<T, T*, const T*> _value;

        T& value();

    public:
        memory_data();
        memory_data(T& t);
        memory_data(const T& t);
        memory_data(T&& t);

        const T& value_const() const;

        const char* name() const override;
        void add(const char* data_ptr, size_t data_size) override;
        const char* ptr() override;
        size_t size() const override;
        void reserve(size_t n) override;
        target_code target() const override;
    };

    template<class T> std::shared_ptr<data> make_memory_data(T&& v);

}} // nxs::network

#include "memory.tcc"

#endif // NETWORK_DATA_MEMORY_H_NXS
