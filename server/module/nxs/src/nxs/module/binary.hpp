#ifndef MODULE_BINARY_H_NXS
#define MODULE_BINARY_H_NXS

#include <nxs/module/base.hpp>
#include <nxs/os/module.hpp>

namespace nxs
{
    template<class T>
    class NXS_SHARED binary_module : public base_module<T>
    {
        using Module_main_ptr = int (*)(nxs::nex&);
        using Module_load_ptr = int (*)();

    private:
        NXS_OS_MODULE_HANDLE _handle;
        std::function<int(nxs::nex&)> _main_ptr;
        std::function<int()> _load_ptr;

    public:
        binary_module(int id);

        bool load();
        void unload();
        int process(nxs::nex& nex);
    };
} // nxs

#include "binary.tpp"

#endif // MODULE_BINARY_H_NXS
