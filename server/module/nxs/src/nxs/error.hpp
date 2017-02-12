#ifndef CORE_ERROR_H_NXS
#define CORE_ERROR_H_NXS

#include <nxs/share.hpp>
#include <nxs/log.hpp>

#include <exception>
#include <string>
#include <map>

#define nxs_error_impl(code, data, ...) nxs::error::add("nxs", code, data, nxs::log::system, __PRETTY_FUNCTION__, NXS_LINE)
#define nxs_error(...) nxs_error_impl(__VA_ARGS__, 0)

namespace nxs
{
    extern NXS_SHARED std::map<int, std::string> error_message_;

    // class
    class NXS_SHARED error : public std::exception
    {
    private:
        std::string _source;
        int _code;
        std::string _data;
        std::string _message;

    public:
        error(const std::string& source,
              int code,
              const std::string& data = "",
              const log::type& type = log::system,
              const std::string& func = "",
              const std::string& line = "");
        const char* what() const throw();
        int code() const;
        const std::string& data() const;
        ~error() throw() {};

    static void add(const std::string& source,
              int code,
              const std::string& data = "",
              const log::type& type = log::system,
              const std::string& func = "",
              const std::string& line = "");
    static void add(int code, const std::string& data = "");
    static void add(int code, int data);
    static void NXS_SHARED add(const std::string& data);

    };

    std::string NXS_SHARED error_str(int code);

    // error code
    namespace errc
    {
        enum errc
        {
            success = 0,
            system,

            connexion,
            connexion_unknown,
            protocol,
            protocol_unknown,
            request_invalid,

            data_overflow,
            data_hdd_read,
            data_hdd_write,

            dataconnexion_fail,
            database_query,

            serialize,

            resource_denied,
            resource_connexion_del,

            user_login,
            user_exist,
            user_get_fail,
            group_del,

            command_unknown,
            command_invalid,
            command_denied,
            command_param_missing,
            command_header_param_missing,

            module,
            module_unknown,
            module_load_fail,

            interface,
            interface_unknown,
            interface_load_fail
        };
    } // errc
}

#endif // CORE_ERROR_H_NXS
