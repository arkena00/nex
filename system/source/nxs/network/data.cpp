#include <nxs/network/data.hpp>
#include <iostream>
namespace nxs{namespace network
{
    data::data() :
        m_transfer_init(false),
        m_transfer_size(0)
    {}

    size_t data::transfer_size() const
    {
        return m_transfer_size;
    }

    void data::transfer_init()
    {
        m_transfer_time_begin = std::chrono::high_resolution_clock::now();
        m_transfer_init = true;
    }

    // add n bytes to transfer size
    void data::transfer_add(size_t n)
    {
        // check if transfer is initialized
        if (!m_transfer_init) transfer_init();

        m_transfer_size += n;

        // transfer is complete
        if (m_transfer_size > size()) m_transfer_size = size();
    }

    void data::transfer_set(size_t n)
    {
        // check if transfer is initialized
        if (!m_transfer_init) transfer_init();

        m_transfer_size = n;
    }

    float data::transfer_progress() const
    {
        return m_transfer_size / static_cast<float>(size());
    }

    float data::transfer_speed() const
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto d = std::chrono::duration_cast<std::chrono::seconds>(now - m_transfer_time_begin);

        return static_cast<float>(transfer_size()) / d.count() / 1000;
    }

    size_t data::transfer_elapsed_time() const
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto d = std::chrono::duration_cast<std::chrono::seconds>(now - m_transfer_time_begin);
        return d.count();
    }

    bool data::transfer_complete() const
    {
        return m_transfer_size == size();
    }
}} // nxs::network
