#ifndef CORE_LOG_H_NXS
#define CORE_LOG_H_NXS

#include <nxs/share.hpp>

#include <string>
#include <vector>
#include <functional>

#define NXS_STRINGIFY(x) #x
#define NXS_TOSTRING(x) NXS_STRINGIFY(x)
#define NXS_LINE  __FILE__ ":" NXS_TOSTRING(__LINE__)

#define nxs_log_impl(message, type, ...) nxs::log::add(message, type, "nxs", nxs::log::note, __PRETTY_FUNCTION__, NXS_LINE)
#define nxs_log(...) nxs_log_impl(__VA_ARGS__, nxs::log::system)

#define nxs_warning_impl(message, type, ...) nxs::log::add(message, type, "nxs", nxs::log::warning, __PRETTY_FUNCTION__, NXS_LINE)
#define nxs_warning(...) nxs_warning_impl(__VA_ARGS__, nxs::log::system)

namespace nxs
{
    class NXS_SHARED log
    {
    private:
        static std::vector<std::string> type_str_;
        static std::vector<std::string> level_str_;
        static std::function<void(const std::string&)> redirect_;
        static bool list_mod_;

        log();

    public:
        enum type { system, network, database };
        enum level { note, warning, error };

        static void add(const std::string& message,
                        const log::type& type = system,
                        const std::string& source = "nxs",
                        const log::level& level = note,
                        const std::string& func = "",
                        const std::string& line = "");
        static void output(const std::string& message);
        static void redirect_output(std::function<void(const std::string&)> fn);

        static void list(const log::type& type, const std::string& message);
        static void list();
    };
} // nxs

#endif // LOG_H_NXS
