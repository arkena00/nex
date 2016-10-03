#ifndef NETWORK_REQUEST_H_NXS
#define NETWORK_REQUEST_H_NXS

#include <nxs/os/share.hpp>
#include <nds/encoder.hpp>
#include <nxs/network/request_base.hpp>
#include <nxs/network/param.hpp>
#include <nxs/network/data.hpp>
#include <string>
#include <vector>
#include <memory>

namespace nxs
{
    namespace network { class protocol; }

    class NXS_SHARED request : public request_base
    {
        friend class nxs::network::protocol;
        friend class nds::encoder;

    private:
        std::string _version;
        nxs::param_list _param_list;
        size_t _size;

        bool _valid;
        bool _finished;

        std::vector<std::unique_ptr<network::data>> _data;
        bool _data_complete;

    public:
        request();
        request(const std::string& str_request);

        void clear();
        void set(const std::string& str_request);
        size_t size() const;

        void validate();

        bool is_finished() const;
        void finish(bool n);

        nxs::param& param(const std::string& name);
        std::string& param_value(const std::string& name, int index = 0);

        template<class T>
        void add(T data);
        void add(const network::hdd_data& data);
        void add(const network::memory_data& data);

        void file_add(const std::string& path);
        network::data& data(size_t index = 0);
        const network::data& data_const(size_t index = 0) const;
        size_t data_count() const;
        bool data_complete() const;
    };
} // nxs

#include "request.tpp"

#endif // NETWORK_REQUEST_H_NXS
