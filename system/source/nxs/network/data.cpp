#include <nxs/network/data.hpp>
#include <fstream>
#include <string>
#include <iostream>

namespace nxs{namespace network
{
    data::data() :
        _transfer_size(0)
    {}

    size_t data::transfer_size() const { return _transfer_size; }
    void data::transfer_add(size_t n)
    {
        _transfer_size += n;
        if (_transfer_size > size()) _transfer_size = size();
    }
    void data::transfer_set(size_t n) { _transfer_size = n; }
    float data::transfer_progress() const { return _transfer_size / static_cast<float>(size()); }
    bool data::transfer_complete() const { return _transfer_size == size(); }


    hdd_data::hdd_data(const std::string& path) :
        _path(path),
        _size(0),
        _tmp(false)
    {
        std::ifstream in(path, std::ios::in | std::ios::binary);
        in.seekg(0, std::ios::end);
        _size = in.tellg();
    }

    hdd_data::~hdd_data()
    {
        if (_tmp) std::remove(_path.c_str());
    }

    void hdd_data::tmp(bool n)
    {
        _tmp = n;
    }

    void hdd_data::add(const char* data_ptr, size_t data_size)
    {
        std::ofstream output;
        output.open(_path, std::ios::out | std::ios::binary | std::ios::app);
        if (output.is_open())
        {
            output.write(data_ptr, data_size);
            output.close();
            transfer_add(data_size);
        }
        else nxs_error << "can't write data";
    }

    const char* hdd_data::ptr()
    {
        std::ifstream input;
        input.open(_path, std::ios::in | std::ios::binary);
        input.seekg(_transfer_size);

        if (!input.is_open()) nxs_error << "data_hdd_read";
        input.read(_buffer.data(), 1024);

        return _buffer.data();
    }

    data::target_code hdd_data::target() const
    {
        return data::hdd;
    }

    size_t hdd_data::size() const
    {
        return _size;
    }

    void hdd_data::reserve(size_t n)
    {
        _size = n;
    }
}} // nxs::network
