#ifndef MODULE_H_NXS
#define MODULE_H_NXS

#include <nxs/module/common.hpp>

namespace nxs
{
    class NXS_SHARED module : public common_module<module>
    {
    public:
        static const std::string name_;
        static const std::string ext_;

    public:
        constexpr static const auto& db_ref = db::nex.module;
        module(int id);
        module(const std::string& name);
        module(const db::line&);
    };
} // nxs

#endif // MODULE_H_NXS
