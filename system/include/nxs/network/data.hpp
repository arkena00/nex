#ifndef NETWORK_DATA_H_NXS
#define NETWORK_DATA_H_NXS

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

}} // nxs::network

#include "data.tcc"

#endif // NETWORK_DATA_H_NXS
