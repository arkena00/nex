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
    public:
        enum targetc : int { memory, hdd };

    private:
        targetc _target;

    protected:
        size_t _size;
        size_t _transfer_size;

        data(targetc target);

    public:
        virtual ~data() = default;

        virtual void add(const char* data_ptr, size_t data_size) = 0;
        virtual const char* ptr() = 0;

        virtual size_t size() const;
        virtual size_t transfer_size() const;
        virtual void reserve(size_t n);

        targetc target() const;
        void transfer_add(size_t n);
        void transfer_set(size_t n);
        float transfer_progress() const;
        bool transfer_complete() const;

        template<class T = std::string> T get() const;
    };

    using data_ptr = std::shared_ptr<data>;

    class NXS_SHARED memory_data : public data
    {
    private:
        std::vector<char> _data;

    public:
        memory_data();
        memory_data(const char* v_data, size_t data_size);

        size_t size() const override;

        void add(const char* data_ptr, size_t data_size) override;
        const char* ptr() override;
        template<class T> T get() const;

        static data_ptr make(const std::string& v)
        {
            return std::make_shared<memory_data>(v.c_str(), v.size());
        }
    };

    class NXS_SHARED hdd_data : public data
    {
    private:
        std::string _path;
        bool _tmp;
        std::array<char, 1024> _buffer;

    public:
        hdd_data(const std::string& path);
        ~hdd_data();

        void tmp(bool n);
        void add(const char* data_ptr, size_t data_size) override;
        const char* ptr() override;

        template<class T> T get() const;
    };

    template<> std::string NXS_SHARED hdd_data::get<std::string>() const;
    template<> std::string NXS_SHARED memory_data::get<std::string>() const;
}} // nxs::network

#include "data.tcc"

#endif // NETWORK_DATA_NXS
