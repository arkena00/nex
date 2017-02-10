#ifndef INTERFACE_H_NXS
#define INTERFACE_H_NXS

#include <nxs/module/common.hpp>

namespace nxs
{
    class interface : public common_module<interface>
    {
    public:
        static const std::string name_;
        static const std::string ext_;

    public:
        constexpr static const auto& db_ref = db::nex.interface;
        interface(int id);
        interface(const std::string& name);
    };
} // nxs

#endif // INTERFACE_H_NXS
