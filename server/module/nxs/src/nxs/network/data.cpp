#include <nxs/network/data.hpp>
#include <fstream>
#include <string>
#include <iostream>

namespace nxs{namespace network
{
    data::data(data::targetc target) :
        _target(target),
        _size(0),
        _transfer_size(0)
    {}

    data::~data() {}

    data::targetc data::target() const { return _target; }
    size_t data::size() const { return _size; }
    size_t data::transfer_size() const { return _transfer_size; }
    void data::resize(size_t n) { _size = n; }


    // memory
    memory_data::memory_data() : data(data::memory) {}
    memory_data::memory_data(const std::string& v) : data(data::memory)
    {
        add(v.c_str(), v.size());
    }

    void memory_data::add(const char* data_ptr, size_t data_size)
    {
        _data.insert(_data.end(), data_ptr, data_ptr + data_size);
        _size += data_size;
    }

    template<>
    std::string memory_data::get<std::string>() const { return std::string(_data.data(), _data.size()); }

    template<>
    const char* memory_data::get<const char*>() const { return _data.data(); }


    hdd_data::hdd_data(const std::string& path) :
        data(data::hdd),
        _path(path),
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

    void hdd_data::tmp(bool n) { _tmp = n; }

    void hdd_data::add(const char* data_ptr, size_t data_size)
    {
        std::ofstream output;
        output.open(_path, std::ios::out | std::ios::binary | std::ios::app);
        if (output.is_open())
        {
            output.write(data_ptr, data_size);
            output.close();
            _transfer_size += data_size;
        }
        else throw nxs_error << "can't write data";
    }

    template<>
    std::string hdd_data::get<std::string>() const { return _path; }
    template<>
    const char* hdd_data::get<const char*>() const { return _path.c_str(); }

}} // nxs::network
