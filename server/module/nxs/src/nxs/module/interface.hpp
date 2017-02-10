#ifndef MODULE_INTERFACE_H_NXS
#define MODULE_INTERFACE_H_NXS

#include <nxs/module/common_module.hpp>

namespace nxs
{
    class interface : public common_module<interface>
    {
    public:
        static const std::string name_;
        static const std::string ext_;

    public:
        interface(int id);
        //interface(const std::string& name);
    };
} // nxs

#endif // MODULE_INTERFACE_H_NXS
