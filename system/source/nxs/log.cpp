#include <nxs/log.hpp>
#include <iostream>

namespace nxs
{
    std::array<std::string, 3> log::type_str_ = { "system", "network", "database" };
    std::array<std::string, 3> log::level_str_ = { "note", "warning", "error" };
    thread_local log* log::instance_ = nullptr;
    std::mutex log::locker_;

    log::log() :
        _level(level::note),
        _pushed(true),
        _mod(mod::none)
    {}

    void log::push(const log::type& type)
    {
        std::string str_level = level_str_[_level];
        std::string source = "nxs";
        std::string message = "[" + source  + ":" + type_str_[type] + "] " + str_level + " - " + _output + "\n";
        if (_level != log::note) message += "at " + _line + "\nin " + _func + "\n";


        locker_.lock();
        std::cout << message;
        if (_redirect) _redirect(_output);
        locker_.unlock();

        clear();
    }

    void log::clear()
    {
        _pushed = true;
        _mod = log::none;
        _output = "";
        _level = log::note;
        _line = "";
        _func = "";
    }

    void log::redirect_output(std::function<void(const std::string&)> fn)
    {
        _redirect = fn;
    }

    log& log::operator<<(const std::string& data)
    {
        _output += data + " ";
        return *this;
    }

    log& log::operator<<(int data)
    {
        _output += std::to_string(data) + " ";
        return *this;
    }

    log& log::operator<<(log::mod log_mod)
    {
        _mod = log_mod;
        return *this;
    }

    log& log::operator<<(log::level log_level)
    {
        _level = log_level;
        return *this;
    }

    // log type specified, push the log
    log& log::operator<<(log::type log_type)
    {
        push(log_type);
        return *this;
    }

    log& log::add(const std::string& line, const std::string& func)
    {
        if (instance_ == nullptr) instance_ = new log;
        if (instance_->_pushed == false && instance_->_mod != list) std::cout << "\nLOG IS NOT PUSHED, ADD LOG TYPE TO PUSH LOG LINE : " << line;
        instance_->_pushed = false;
        instance_->_line = line;
        instance_->_func = func;
        return *instance_;
    }
} // nxs
