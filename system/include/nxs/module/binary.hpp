#ifndef MODULE_BINARY_H_NXS
#define MODULE_BINARY_H_NXS

#include <nxs/module/base.hpp>
#include <nxs/os/module.hpp>

namespace nxs
{
    template<class T>
    class binary_module : public base_module<T>
    {
        using Module_main_ptr = int (*)(nxs::nex&);
        using Module_load_ptr = int (*)();

    private:
        NXS_OS_MODULE_HANDLE m_handle;
        std::function<int(nxs::nex&)> m_main_ptr;
        std::function<int()> m_load_ptr;

    public:
        binary_module(int id);

        virtual bool load();
        virtual void unload() override;
        virtual int process(nxs::nex& nex);
    };
} // nxs

#include "binary.tcc"

#endif // MODULE_BINARY_H_NXS
