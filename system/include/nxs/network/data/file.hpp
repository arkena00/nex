#ifndef NETWORK_DATA_FILE_NXS
#define NETWORK_DATA_FILE_NXS

#include <nxs/network/data.hpp>

namespace nxs{namespace network
{
    class file_data : public data
    {
    private:
        std::string _path;
        size_t _size;
        bool _tmp;
        std::array<char, 1024> _buffer;

    public:
        file_data(const std::string& path);
        ~file_data();

        void tmp(bool n);
        const char* name() const override;
        void add(const char* data_ptr, size_t data_size) override;
        const char* ptr() override;
        target_code target() const override;
        size_t size() const override;
        void reserve(size_t n) override;
    };
}} // nxs::network

#endif // NETWORK_DATA_FILE_NXS
