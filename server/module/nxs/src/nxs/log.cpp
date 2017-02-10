#include <nxs/log.hpp>

#include <iostream>

namespace nxs
{
    std::vector<std::string> log::type_str_ { "system", "network", "database" };
    std::vector<std::string> log::level_str_ { "note", "warning", "error" };
    std::function<void(const std::string&)> log::redirect_;
    bool log::list_mod_ = 0;

    void log::add(const std::string& message, const log::type& type, const std::string& source, const log::level& level, const std::string& func, const std::string& line)
    {
        std::string str_level = level_str_[level];
        std::string str_line = "";
        if (level != log::note) str_line = "at " + line + "\nin " + func + "\n";
        std::string log_msg = "[" + source  + ":" + type_str_[type] + "] " + str_level + " - " + message + "\n" + str_line;
        if (list_mod_) log_msg = message;
        output(log_msg);
    }

    void log::output(const std::string& message)
    {
        std::cout << message;
        if (log::redirect_) log::redirect_(message);
    }

    void log::redirect_output(std::function<void(const std::string&)> fn)
    {
        log::redirect_ = fn;
    }

    void log::list(const log::type& type, const std::string& message)
    {
        add(" ***** " + message + " ***** ", log::system, "nxs");
        list_mod_ = 1;
    }

    void log::list() { list_mod_ = 0; output("\n\n"); }
} // nxs
