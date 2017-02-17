#ifndef CORE_ERROR_H_NXS
#define CORE_ERROR_H_NXS

#include <nxs/share.hpp>
#include <nxs/log.hpp>

#include <exception>
#include <string>
#include <map>

#define nxs_error nxs::error(NXS_LINE, NXS_FUNC_NAME)

namespace nxs
{
    extern NXS_SHARED std::map<int, std::string> error_message_;

    class NXS_SHARED error : public std::exception
    {
    private:
        std::string _line;
        std::string _func;
        std::string _source;
        int _code;
        log::type _type;
        std::string _message;

    public:
        error(const std::string& line, const std::string& func, const std::string& source = "nxs");
        const char* what() const throw() override;
        int code() const;
        ~error() throw();

        error& operator<<(const std::string& data);
        error& operator<<(int data);
        error& operator<<(log::type log_type);

        std::string static str(int code);
    };

    // error code
    namespace errc
    {
        enum errc
        {
            success = 0,
            system,
            database,

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
