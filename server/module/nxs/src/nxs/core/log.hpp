#ifndef CORE_LOG_H_NXS
#define CORE_LOG_H_NXS

#include <nxs/os/share.hpp>

#include <string>
#include <vector>

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
    };
} // nxs

#endif // LOG_H_NXS
