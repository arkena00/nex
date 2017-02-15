#ifndef CORE_LOG_H_NXS
#define CORE_LOG_H_NXS

#include <nxs/share.hpp>
#include <nxs/preprocessor.hpp>

#include <string>
#include <vector>
#include <functional>

#define nxs_log nxs::log::instance(NXS_LINE, NXS_FUNC_NAME)

#define nxs_warning_impl(message, type, ...) nxs::log::stadd(message, type, "nxs", nxs::log::warning, NXS_FUNC_NAME, NXS_LINE)
#define nxs_warning(...) nxs_warning_impl(__VA_ARGS__, nxs::log::system)

namespace nxs
{
    class NXS_SHARED log
    {
    public:
        enum type { system, network, database };
        enum level { note, warning, error };

    public:
        static log* instance_;
        static std::vector<std::string> type_str_;
        static std::vector<std::string> level_str_;


        std::string _output;
        level _level;
        std::string _line;
        std::string _func;
        std::function<void(const std::string&)> _redirect;
        bool _list_mod;

        log();

    public:
        static log& instance(const std::string& line, const std::string& func);

        static void stadd(const std::string& message,
                        const log::type& type = system,
                        const std::string& source = "nxs",
                        const log::level& level = note,
                        const std::string& func = "",
                        const std::string& line = "") {}

        void push(const log::type& type);
        void redirect_output(std::function<void(const std::string&)> fn);

        void list(const log::type& type, const std::string& message);
        void list();

        log& operator<<(const std::string& data);
        log& operator<<(int data);
        log& operator<<(log::type log_type);
    };
} // nxs

#endif // LOG_H_NXS
