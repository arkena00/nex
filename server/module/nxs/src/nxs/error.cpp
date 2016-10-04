#include <nxs/error.hpp>
#include <nxs/log.hpp>

using namespace std;
#include <iostream>
namespace nxs
{
    error::error(const string& source, int code, const string& data, const log::type& type, const std::string& func, const std::string& line)
    {
        _source = source;
        _code = code;
        _data = data;
        _message = error_str(_code) + " : " + _data;

        log::add(_message, type, _source, log::error, func, line);
    }

    const char* error::what() const throw()
    {
        return _message.c_str();
    }

    int error::code() const { return _code; }
    const string& error::data() const { return _data; }

    void error::add(const string& source, int code, const string& data, const log::type& type, const std::string& func, const std::string& line)
    {
        throw error("nxs", code, data, type, func, line);
    }

    void error::add(int code, const string& data) { add("nxs", code, data); }
    void error::add(int code, int data) { add(code, to_string(data)); }
    void error::add(const string& data) { add("module", errc::module, data); }

    string error_str(int code)
    {
        if (error_message_.count(code) == 0) return "error_code : " + to_string(code);
        return error_message_[code];
    }

} // nxs
