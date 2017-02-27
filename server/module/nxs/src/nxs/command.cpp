#include <nxs/command.hpp>
#include <nxs/core.hpp>
#include <nxs/error.hpp>
#include <nxs/network/request.hpp>

namespace nxs
{
    using Command_List = std::map<std::string, command>;
    Command_List command::list_;

    template<>
    void command::init_loop<command::size_>() {}

    command::command(const std::string& module, const std::string& name, std::function<void(nxs::nex&)> fn) :
        request_base(request_base::module, module, name),
        _id(0),
        _address(fn),
        _wait_transfer(true)
    {}

    int command::id() const { return _id; }
    const nxs::param_list& command::param_list() const { return _param_list; }
    const std::function<void(nxs::nex&)>& command::address() const { return _address; }
    const std::string& command::help() const { return _help; }
    void command::help_set(const std::string& text) { _help = text; }

    void command::wait_transfer(bool n) { _wait_transfer = n; }
    bool command::wait_transfer() const { return _wait_transfer; }

    void command::execute(nxs::nex& nex) const
    {
        if (!nex.transfer_complete() && wait_transfer()) return;
        address()(nex);
    }

    void command::param_add(const std::string& name, const param::modc& mod, const std::string& default_value, const std::string& format)
    {
        nxs::param p(name, mod, default_value, format);
        _param_list.add(p);
    }

    command& command::add(const std::string& module, const std::string& name, std::function<void(nxs::nex&)> fn)
    {
        nxs::command cmd(module, name, fn);
        std::string command_name = cmd.full_command_name();
        list_.insert(std::make_pair(command_name, std::move(cmd)));
        return list_.at(command_name);
    }

    const Command_List& command::get() { return list_; }

    const command& command::get(const std::string& full_command_name)
    {
        if (!exist(full_command_name)) nxs_error << "command unknown :" << full_command_name;
        return list_.at(full_command_name);
    }

    bool command::exist(const std::string& full_command_name) { return list_.count(full_command_name) > false ? true : false; }

    void command::init()
    {
        command::init_loop();
    }
} // nxs
