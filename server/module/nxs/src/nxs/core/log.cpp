#include <nxs/core/log.hpp>

#include <iostream>

std::vector<std::string> nxs::log::type_str_ { "system", "network", "database" };
std::vector<std::string> nxs::log::level_str_ { "note", "warning", "error" };

namespace nxs
{
    void log::add(const std::string& message, const log::type& type, const std::string& source, const log::level& level, const std::string& func, const std::string& line)
    {
        std::string str_level = level_str_[level];
        std::string str_line = "";
        if (level != log::note) str_line = "at " + line + "\nin " + func + "\n";
        std::string log_msg = "[" + source  + ":" + type_str_[type] + "] " + str_level + " - " + message + "\n" + str_line;
        output(log_msg);
    }

    void log::output(const std::string& message)
    {
        std::cout << message;
    }

} // nxs
