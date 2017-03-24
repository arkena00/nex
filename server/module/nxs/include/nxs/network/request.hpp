#ifndef NETWORK_REQUEST_H_NXS
#define NETWORK_REQUEST_H_NXS

#include <nxs/share.hpp>
#include <nds/encoder.hpp>
#include <nxs/network/io.hpp>
#include <nxs/network/request_base.hpp>
#include <nxs/network/param.hpp>
#include <nxs/network/data.hpp>
#include <string>
#include <vector>
#include <memory>

namespace nxs
{
    namespace network { template<io::type> class basic_protocol; }

    class NXS_SHARED request : public request_base
    {
        template<io::type IO_Type> friend class nxs::network::basic_protocol;
        friend class nds::encoder<>;

    private:
        std::string _version;
        nxs::param_list _param_list;
        size_t _size;

        bool _valid;

        std::vector<std::shared_ptr<network::data>> _data;

    public:
        using linear_type = std::string;

        request();
        request(const std::string& str_request);

        //request(const request&) {}

        void clear();
        void set(const std::string& str_request);
        size_t size() const;

        void validate();

        nxs::param& param(const std::string& name);
        std::string& param_value(const std::string& name, int index = 0);

        template<class T>
        void add(T data);
        void add(const network::hdd_data& data);
        void add(const network::memory_data& data);
        void add(const request::linear_type& data);

        void file_add(const std::string& path);
        network::data& data(size_t index = 0);
        const network::data& data_const(size_t index = 0) const;
        size_t data_count() const;
    };
} // nxs


// request codecs
namespace nds
{
    template<> NXS_SHARED std::string encoder<>::encode<std::string, nxs::header>(const std::vector<size_t>& value_list);
    template<> NXS_SHARED std::string encoder<>::encode<std::string, nxs::header>(const std::string& v);
    template<> NXS_SHARED std::string encoder<>::encode<std::string>(const nxs::request& req);

    template<> NXS_SHARED size_t encoder<>::decode<size_t, nxs::header>(const std::string& v);
    template<> NXS_SHARED std::string encoder<>::decode<std::string, nxs::header>(const std::string& v);
    template<> NXS_SHARED void encoder<>::decode(const std::string& str_request, nxs::request& req);
} // nds

#include "request.tpp"

#endif // NETWORK_REQUEST_H_NXS
