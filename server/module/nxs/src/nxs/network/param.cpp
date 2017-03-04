#include <nxs/network/param.hpp>
#include <nxs/error.hpp>
#include <nxs/log.hpp>
#include <regex>
#include <iostream>

namespace nds
{
    template<> int encoder::decode<int, nxs::param>(const std::string& v) { return std::stoi(v); }
    template<> size_t encoder::decode<size_t, nxs::param>(const std::string& v) { return std::stoi(v); }
    template<> std::string encoder::decode<std::string, nxs::param>(const std::string& v) { return v; }
} // nds

namespace nxs
{
    using Param_List = std::map<std::string, nxs::param>;

    param::param(const std::string& name, modc v_mod, const std::string& value, const std::string& v_format) :
        _name(name),
        _mod(v_mod),
        _format(v_format)
    { _value[0] = value; }
    param::param(const std::string& name, const std::string& value) : param(name, modc::require, value) {}

    param::~param() { _value.clear(); }

    std::string& param::operator[](int index) { return _value[index]; }

    const std::string& param::name() const { return _name; }
    const std::string& param::format() const { return _format; }
    const std::map<int, std::string>& param::value_list() const { return _value; }
    param::modc param::mod() const { return _mod; }
    size_t param::size() const { return _value.size(); }
    void param::add(const std::string& value) { _value.insert(make_pair(_value.size(), value)); }

    bool param::is_overwrite() const { return (_mod == overwrite) ? true : false; }
    bool param::is_required() const { return (_mod == require) ? true : false; }

    nxs::param& param_list::operator[](const std::string& name)
    {
        if (!exist(name)) { nxs_warning << "trying to access inexistant parameter" << name << log::system; }
        return _list[name];
    }

    param_list::const_iterator param_list::begin() const { return _list.begin(); }
    param_list::const_iterator param_list::end() const { return _list.end(); }
    param_list::iterator param_list::begin() { return _list.begin(); }
    param_list::iterator param_list::end() { return _list.end(); }

    void param_list::add(const param& p)
    {
        _list.insert(std::make_pair(p.name(), p));
    }
    void param_list::clear() { _list.clear(); }
    size_t param_list::size() const { return _list.size(); }
    bool param_list::exist(const std::string& name) const { return _list.count(name) ? true : false; }

    void param_list::parse(const std::string& str_param_list)
    {
        clear();

        std::string param_name = "", param_value = "";
        size_t param_start = 0, param_end = 0;
        size_t value_start = 0, value_end = 0;
        size_t escape_pos = 0;
        bool escape = 0, read_param_name = 1;

        for (size_t i = 0; i != str_param_list.size() - 1; i++)
        {
            if (str_param_list.at(i) == '\\') escape_pos = i;
            if (escape_pos > 0 && (escape_pos == i - 1)) escape = 1;

            if (str_param_list.at(i) == '=' && !escape && read_param_name)
            {
                read_param_name = 0;

                param_end = i;
                value_start = param_end + 1;
                param_name = str_param_list.substr(param_start, param_end - param_start);
            }

            if (str_param_list.at(i) == ';' && !escape)
            {
                read_param_name = 1;

                value_end = i;
                param_start = value_end + 1;
                param_value = str_param_list.substr(value_start, value_end - value_start);
                // remove escaped chars
                param_value = std::regex_replace(param_value, std::regex("(\\\\;)"), ";");

                if (param_name == "") nxs_error << "param parse error";
                if (!exist(param_name)) _list.insert(make_pair(param_name, nxs::param(param_name, param::require, param_value)));
                else _list[param_name][_list[param_name].size()] = param_value;

                value_start = value_end + 1;
            }
            escape = 0;
        }
    }
}
