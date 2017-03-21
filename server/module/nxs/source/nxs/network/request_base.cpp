#include <nxs/network/request_base.hpp>

namespace nxs
{
    request_base::request_base() : _module_type(unknown) {}

    request_base::request_base(module_typec module_type, const std::string& module_name, const std::string& command_name) :
        _module_type(module_type),
        _module_name(module_name),
        _command_name(command_name)
    {}

    request_base::module_typec request_base::module_type() const { return _module_type; }
    const std::string& request_base::module_name() const { return _module_name; }
    const std::string& request_base::command_name() const { return _command_name; }
    const std::string request_base::full_command_name() const
    {
        if (_module_type == module) return _module_name + "::" + _command_name;
        return _module_name + ":" + _command_name;
    }

     const request_base::header_list& request_base::header_get() const { return _header_list; }
     size_t request_base::header_count() const { return _header_list.size(); }
     bool request_base::header_exist(header::code id) const { return _header_list.count(id); }

} // nxs
