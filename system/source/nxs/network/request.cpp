#include <nxs/network/request.hpp>
#include <nxs/error.hpp>
#include <nxs/command.hpp>
#include <nds/encoder.hpp>
#include <regex>

using namespace std;

/// format:    NEX:1.0/header_param=header_value;/nxs::test;;bin_data

namespace nxs
{
    request::request()
    {
        set("nxs::null;");
    }
    request::request(const std::string& str_request)
    {
        set(str_request);
    }

    void request::clear()
    {
        _version = "1.0";
        _module_type = request_base::unknown;
        _module_name = "";
        _command_name = "";
        _size = 0;
        _valid = false;
        _data.clear();
        _header_list.clear();
        _param_list.clear();
    }

    void request::set(const std::string& str_request)
    {
        clear();
        if (str_request.empty())
        {
            nds::encoder<>::decode(std::string("NEX:1.0//nxs::null;;"), *this);
            return;
        }
        if (str_request.substr(0, 3) != "NEX") nds::encoder<>::decode("NEX:1.0//" + str_request + ";", *this);
        else nds::encoder<>::decode(str_request, *this);
    }

    size_t request::size() const { return _size; }

    void request::validate()
    {
        // validate nxs commands and module registered commmands
        if (!command::exist(full_command_name()) && module_name() != "nxs") return;

        // get registered command
        const nxs::command& cmd = nxs::command::get(full_command_name());

        // validate headers
        for (auto& it : _header_list)
        {
            auto hid = it.first;
            // overwrite headers defined by command
            if (cmd.header_exist(hid)) header(hid) = cmd.header(hid);
        }

        // validate param
        for (auto& it : cmd.param_list())
        {
            const nxs::param& p = it.second;
            // overwrite request param
            if (p.is_overwrite()) _param_list[p.name()] = p;
            // param is required && missing
            if (p.is_required() && !_param_list.exist(p.name()))
            {
                // no default value
                if (p.value().empty()) nxs_error << "command_param_missing" << p.name();
                // else use default value
                _param_list.add(p);
            }
            // check format for each value
            if (p.format() != "" && p.size() > 0)
            {
                for (size_t i = 0; i != _param_list[p.name()].size(); i++)
                {
                    if (!std::regex_match(_param_list[p.name()][i], std::regex("(" + p.format() + ")")))
                        nxs_error << "command_invalid, wrong format for " << p.name() <<
                                  ", value : " << _param_list[p.name()][i] <<
                                  ", expected : " << p.format();
                }
            }
        }
        _valid = true;
    }

    nxs::param& request::param(const std::string& name) { return _param_list[name]; }
    std::string& request::param_value(const std::string& name, int index)  { return _param_list[name][index]; }


    void request::add(network::file_data&& d)
    {
        _data.emplace_back(std::make_shared<network::file_data>(std::move(d)));
    }

    void request::add(network::memory_data<request::linear_type>&& d)
    {
        _data.push_back(std::make_shared<network::memory_data<request::linear_type>>(std::move(d)));
    }

    // add linear data used by request
    void request::add(request::linear_type data)
    {
        header_add<headers::data_size>(data.size());
        _data.emplace_back(std::make_shared<network::memory_data<request::linear_type>>(std::move(data)));
    }

    void request::file_add(const std::string& path)
    {
        header_add<headers::data_size>(_data.back().get()->size());
        header_add<headers::user_name>("ads");
        _data.emplace_back(std::make_shared<network::file_data>(path));
    }

    network::data& request::data(size_t index)
    {
        if (index >= _data.size()) nxs_error << "request data out of range";
        return *_data[index];
    }

    std::shared_ptr<network::data> request::data_ptr(size_t index)
    {
        if (index >= _data.size()) nxs_error << "request data out of range";
        return _data[index];
    }

    size_t request::data_count() const { return _data.size(); }
} // nxs

