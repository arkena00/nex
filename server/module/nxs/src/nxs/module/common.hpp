#ifndef MODULE_COMMON_H_NXS
#define MODULE_COMMON_H_NXS

#include <nxs/module/binary.hpp>
#include <nxs/module/text.hpp>

namespace nxs
{
    template<class T>
    class common_module : public base_module<T>
    {
    private:
        bool load() { return false; }
        int process(nxs::nex& nex) { return 0; }

    protected:
        common_module(int id);
        //common_module(const std::string& name);

    public:
        static void init();
        static bool load(int id, const std::string& ext);
        template<class M_Type> static bool load(int id);
    };
} // nxs

#include "common.tpp"

#endif // MODULE_COMMON_H_NXS
