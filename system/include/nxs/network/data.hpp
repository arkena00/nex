#ifndef NETWORK_DATA_NXS
#define NETWORK_DATA_NXS

#include <nxs/share.hpp>
#include <nxs/utility/trait.hpp>
#include <string>
#include <vector>
#include <memory>
#include <array>

namespace nxs{namespace network
{
    class NXS_SHARED data
    {
    protected:
        size_t _transfer_size;

        data();

    public:
        enum target_code : int { memory, hdd };

        virtual ~data() = default;

        virtual void add(const char* data_ptr, size_t data_size) = 0;
        virtual const char* ptr() = 0;
        virtual target_code target() const = 0;
        virtual size_t size() const = 0;
        virtual void reserve(size_t n) = 0;

        size_t transfer_size() const;

        void transfer_add(size_t n);
        void transfer_set(size_t n);
        float transfer_progress() const;
        bool transfer_complete() const;

        template<class T = std::string> T get() const;
    };

    using shared_data = std::shared_ptr<data>;

    template<class T>
    class memory_data : public data
    {
    private:
        T _data;

    public:
        memory_data() {}
        memory_data(const T& t) : _data(t) {}
        memory_data(T& t) : _data(t) {}
        memory_data(T&& t) : _data(std::move(t)) {}

        void add(const char* data_ptr, size_t data_size) override
        {
            _data.insert(_data.end(), data_ptr, data_ptr);
        }

        const char* ptr() override
        {
            return _data.data();
        }

        size_t size() const override
        {
            return _data.size();
        }

        void reserve(size_t n) override
        {
            _data.reserve(n);
        }

        target_code target() const override
        {
            return data::memory;
        }
    };

    template<class T>
    network::shared_data make_memory_data(T&& v)
    {
        return std::make_shared<memory_data<T>>(std::move(v));
    }


    class NXS_SHARED hdd_data : public data
    {
    private:
        std::string _path;
        size_t _size;
        bool _tmp;
        std::array<char, 1024> _buffer;

    public:
        hdd_data(const std::string& path);
        ~hdd_data();

        void tmp(bool n);
        void add(const char* data_ptr, size_t data_size) override;
        const char* ptr() override;
        target_code target() const override;
        size_t size() const override;
        void reserve(size_t n) override;
    };
}} // nxs::network

#include "data.tcc"

#endif // NETWORK_DATA_NXS
