#include <nxs/error.hpp>
#include <nxs/log.hpp>

#include <iostream>
namespace nxs
{
    error::error(const std::string& line, const std::string& func, const std::string& source) :
        _line(line),
        _func(func),
        _source(source),
        _type(log::system)
    {}

    error::~error() throw()
    {
        log::add(_line, _func) << _message << log::error << _type;
    };

    const char* error::what() const throw()
    {
        return _message.c_str();
    }

    int error::code() const { return _code; }

    error& error::operator<<(const std::string& data)
    {
        _message += data;
        return *this;
    }

    error& error::operator<<(int data)
    {
        _message += std::to_string(data);
        return *this;
    }

    error& error::operator<<(log::type log_type)
    {
        _type = log_type;
        return *this;
    }

    std::string error::str(int code)
    {
        if (error_message_.count(code) == 0) return "error_code : " + std::to_string(code);
        return error_message_[code];
    }
} // nxs
