#include <nxs/network/header.hpp>
#include <nxs/network/protocol/nex.hpp>
#include <nxs/command.hpp>
#include <nxs/config.hpp>

namespace nds
{
    template<> std::string encoder<>::encode<std::string, nxs::header>(const std::vector<size_t>& value_list)
    {
        std::string result = "";
        for (auto it : value_list)
        {
            result += std::to_string(it) + ";";
        }
        return result.substr(0, result.size() - 1);
    }
    template<> std::string encoder<>::encode<std::string, nxs::header>(const std::string& v) { return v; }
    template<> std::string encoder<>::encode<std::string, nxs::header>(const size_t& v) { return std::to_string(v); }
} // nds

namespace nxs
{
    std::vector<header::code> header::list_;
    std::map<std::string, header::code> header::code_;
    std::vector<std::function<header*()>> header::reflector_list_;

    template<>
    void header::init<header::size_>() {}

    std::unique_ptr<header> header::make(const std::string& name)
    {
        if (!code_.count(name)) nxs_error << "header not found :" << name;
        return make(code_[name]);
    }
    std::unique_ptr<header> header::make(header::code id) { return std::unique_ptr<header>(reflector_list_[id]()); }


    header::header(header::code id, const std::string& name) :
        _id(id),
        _name(name)
    {}

    header::code header::id() const { return _id; }
    const std::string& header::name() const { return _name; }

    namespace headers
    {
        size_t req_id::id_ = 0;

        void req_id::preprocess(network::protocol& nex)
        {
            // transfer input req_id to output
            if (nex.input().header_exist<headers::req_id>())
            {
                size_t id = nex.input().header_value<headers::req_id>();
                nex.output().header_add<headers::req_id>(id);
            }
        }

        void data_size::preprocess(network::protocol& nex)
        {
            _data_index = 0;
            _data_offset = 0;

            try {
            nex.transfer_complete(false);
            // data target, default target is memory
            int target = data_target::memory;
            if (nex.input().header_exist<headers::data_target>()) target = nex.input().header<headers::data_target>().value();
            // data
            size_t data_count = 0;
            data_count = nex.input().header<headers::data_size>().size();
            if (data_count > 0)
            {
                // init all data
                for (size_t i = 0; i < data_count; i++)
                {
                    size_t data_size = nex.input().header<headers::data_size>().value(i);
                    // hdd data
                    if (target == headers::data_target::hdd)
                    {
                        network::hdd_data d(nxs::config::network_download_path + "__tmp" + std::to_string(nex.connexion().id()) + std::to_string(i));
                        d.tmp(true);
                        d.reserve(data_size);
                        nex.input().add(d);
                    }
                    // memory data
                    else
                    {
                        network::memory_data d;
                        d.reserve(data_size);
                        nex.input().add(d);
                    }
                }
                // init first data
                _data_offset = nex.input().size();
            }
            } catch (const std::exception& e) { nxs_error << "header data_size init fail :" << e.what(); }
        }

        void data_size::process(network::protocol& nex)
        {
            if (nex.transfer_complete()) return;

            network::data& current = nex.input().data(_data_index);
            size_t write_size = nex.connexion().buffer().size() - _data_offset;

            // end of current data
            if (current.transfer_size() + write_size >= current.capacity())
            {
                write_size = write_size - (current.transfer_size() + write_size - current.capacity());
                current.add(nex.connexion().buffer().data() + _data_offset, write_size);
                // next data
                _data_index++;
                if (_data_index == nex.input().data_count()) // last data
                {
                    _data_index = 0;
                    _data_offset = 0;
                    nex.transfer_complete(true);
                    return;
                }
                _data_offset += write_size;
                process(nex);
            }
            else if (write_size > 0) current.add(nex.connexion().buffer().data() + _data_offset, write_size);

            _data_offset = 0;
        }

        void user_name::preprocess(network::protocol& nex)
        {
            //std::cout << "\nINIT USER : " << nex.input().header<headers::user_name>().value();
        }
    } // headers
} // nxs
