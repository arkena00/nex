#include <nxs/network/request.hpp>
#include <nxs/constant.hpp>
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
        _finished = false;
        _data.clear();
        _data_complete = false;
        _header_list.clear();
        _param_list.clear();
    }

    void request::set(const std::string& str_request)
    {
        clear();
        if (str_request.substr(0, 3) != "NEX") nds::encoder::decode("NEX:1.0//" + str_request + ";", *this);
        else nds::encoder::decode(str_request, *this);;
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
                if (p.value().empty()) nxs_error(errc::command_param_missing, p.name());
                // else use default value
                _param_list.add(p);
            }
            // check format for each value
            if (p.format() != "" && p.size() > 0)
            {
                for (size_t i = 0; i != _param_list[p.name()].size(); i++)
                {
                    if (!std::regex_match(_param_list[p.name()][i], std::regex("(" + p.format() + ")")))
                        nxs_error(errc::command_invalid, "wrong format for " + p.name() +
                                  ", value : " + _param_list[p.name()][i] +
                                  ", expected : " + p.format());
                }
            }
        }
        _valid = true;
    }

    bool request::is_finished() const { return _finished; }
    void request::finish(bool n) { _finished = n; }

    nxs::param& request::param(const std::string& name) { return _param_list[name]; }
    std::string& request::param_value(const std::string& name, int index)  { return _param_list[name][index]; }

    void request::add(const network::memory_data& d) { _data.push_back(std::make_unique<network::memory_data>(d)); }
    void request::add(const network::hdd_data& d) { _data.push_back(std::make_unique<network::hdd_data>(d)); }

    void request::file_add(const std::string& path)
    {
        _data.push_back(std::make_unique<network::hdd_data>(path));
        header_add<headers::data_size>(_data.back().get()->size());
        header_add<headers::user_name>("ads");
    }

    network::data& request::data(size_t index)
    {
        if (index >= _data.size()) nxs_error(errc::system, "request data out of range");
        return *_data[index];
    }
    const network::data& request::data_const(size_t index) const
    {
        if (index >= _data.size()) nxs_error(errc::system, "request data out of range");
        return *_data.at(index);
    }

    size_t request::data_count() const { return _data.size(); }
    bool request::data_complete() const { return _data_complete; }

} // nxs

