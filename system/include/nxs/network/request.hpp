#ifndef NETWORK_REQUEST_H_NXS
#define NETWORK_REQUEST_H_NXS

#include <nxs/share.hpp>
#include <nds/encoder.hpp>
#include <nxs/network/io.hpp>
#include <nxs/network/request_base.hpp>
#include <nxs/network/data/file.hpp>
#include <nxs/network/data/memory.hpp>
#include <string>
#include <vector>
#include <memory>

namespace nxs
{
    namespace network { template<io::type> class basic_protocol; template<class> class memory_data; class file_data; }

    class NXS_SHARED request : public request_base
    {
        template<io::type IO_Type> friend class nxs::network::basic_protocol;
        friend class nds::encoder<>;

    public:
        using linear_type = std::string;

    private:
        std::string _version;
        size_t _size;

        bool _valid;

        std::vector<std::shared_ptr<network::data>> _data;

    public:
        request();
        request(const std::string& str_request);


        void clear();
        void set(const std::string& str_request);
        size_t size() const;

        void validate();

        nxs::param& param(const std::string& name);
        std::string& param_value(const std::string& name, int index = 0);

        void add(network::file_data&& data);
        void add(network::memory_data<request::linear_type>&& data);
        void data_add(request::linear_type data);

        template<class T>
        void add(T data);

        void file_add(const std::string& path);

        network::data& data(size_t index = 0);
        std::shared_ptr<network::data> data_ptr(size_t index = 0);
        size_t data_count() const;
    };
} // nxs


// request codecs
namespace nds
{
    template<> std::string encoder<>::encode<std::string, nxs::header>(const std::vector<size_t>& value_list);
    template<> std::string encoder<>::encode<std::string, nxs::header>(const std::string& v);
    template<> std::string encoder<>::encode<std::string>(const nxs::request& req);

    template<> size_t encoder<>::decode<size_t, nxs::header>(const std::string& v);
    template<> std::string encoder<>::decode<std::string, nxs::header>(const std::string& v);
    template<> void encoder<>::decode(const std::string& str_request, nxs::request& req);
} // nds

#include "request.tcc"

#endif // NETWORK_REQUEST_H_NXS
