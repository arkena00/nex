#ifndef NETWORK_DATA_NXS
#define NETWORK_DATA_NXS

#include <nxs/share.hpp>
#include <nxs/utility/trait.hpp>
#include <string>
#include <vector>

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
        virtual ~data();

        targetc target() const;
        size_t size() const;
        size_t transfer_size() const;
        void resize(size_t n);

        virtual void add(const char* data_ptr, size_t data_size) = 0;
        template<class T = std::string> T get() const;
    };


    class NXS_SHARED memory_data : public data
    {
    private:
        std::vector<char> _data;
    public:
        memory_data();
        memory_data(const std::string&);
        template<class T, nxs::enable_if<std::is_arithmetic<T>::value>...>
        memory_data(T data);

        virtual void add(const char* data_ptr, size_t data_size) override;
        template<class T> T get() const;
    };

    class NXS_SHARED hdd_data : public data
    {
    private:
        std::string _path;
        bool _tmp;

    public:
        hdd_data(const std::string& path);
        ~hdd_data();

        void tmp(bool n);
        virtual void add(const char* data_ptr, size_t data_size) override;
        template<class T> T get() const;
    };
}} // nxs::network

#include "data.tpp"

#endif // NETWORK_DATA_NXS
