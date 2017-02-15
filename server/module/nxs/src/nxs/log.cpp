#include <nxs/log.hpp>

#include <iostream>

namespace nxs
{
    std::vector<std::string> log::type_str_ { "system", "network", "database" };
    std::vector<std::string> log::level_str_ { "note", "warning", "error" };
    log* log::instance_ = nullptr;

    log::log() : _list_mod(false)
    {

    }

    log& log::instance(const std::string& line, const std::string& func)
    {
        if (instance_ == nullptr) instance_ = new log;
        instance_->_line = line;
        instance_->_func = func;
        return *instance_;
    }

    void log::push(const log::type& type)
    {
        std::string str_level = level_str_[_level];
        std::string source = "nxs";
        std::string message = "[" + source  + ":" + type_str_[type] + "] " + str_level + " - " + _output + "\n";
        if (_level != log::note) message += "at " + _line + "\nin " + _func + "\n";
        //if (_list_mod) log_msg = message;

        std::cout << message;
        if (_redirect) _redirect(_output);

        // clear output
        _output = "";
    }

    void log::redirect_output(std::function<void(const std::string&)> fn)
    {
        _redirect = fn;
    }

    void log::list(const log::type& type, const std::string& message)
    {
        //add(" ***** " + message + " ***** ", log::system, "nxs");
        _list_mod = 1;
    }

    void log::list() { /*_list_mod = 0; output("\n\n");*/ }

    log& log::operator<<(const std::string& data)
    {
        _output += data + " ";
        return *this;
    }

    log& log::operator<<(int data)
    {
        _output += std::to_string(data);
        return *this;
    }

    // log type specified, push the log
    log& log::operator<<(log::type log_type)
    {
        push(log_type);
        return *this;
    }
} // nxs
