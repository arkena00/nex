#include <nxs/network/data/file.hpp>
#include <fstream>

namespace nxs{namespace network
{
    file_data::file_data(const std::string& path) :
    _path(path),
    _tmp(false)
    {
        std::ifstream in(path, std::ios::in | std::ios::binary);
        in.seekg(0, std::ios::end);
        _size = static_cast<size_t>(in.tellg());
    }

    file_data::~file_data()
    {
        if (_tmp) std::remove(_path.c_str());
    }

    void file_data::tmp(bool n)
    {
        _tmp = n;
    }

    const char* file_data::name() const
    {
        return _path.c_str();
    }

    void file_data::add(const char* data_ptr, size_t data_size)
    {
        std::ofstream output;
        output.open(_path, std::ios::out | std::ios::binary | std::ios::app);
        if (output.is_open())
        {
            output.write(data_ptr, data_size);
            output.close();
            transfer_add(data_size);
        }
        else nxs_error << "can't write data" << log::system;
    }

    const char* file_data::ptr()
    {
        std::ifstream input;
        input.open(_path, std::ios::in | std::ios::binary);
        input.seekg(m_transfer_size);

        if (!input.is_open()) nxs_error << "data_hdd_read" << log::system;
        input.read(_buffer.data(), 1024);

        return _buffer.data();
    }

    data::target_code file_data::target() const
    {
        return data::hdd;
    }

    size_t file_data::size() const
    {
        return _size;
    }

    void file_data::reserve(size_t n)
    {
        _size = n;
    }
}} // nxs::network
