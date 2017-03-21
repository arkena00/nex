#ifndef MODULE_COMMON_H_NXS
#define MODULE_COMMON_H_NXS

#include <nxs/module/binary.hpp>
#include <nxs/module/text.hpp>

namespace nxs
{
    template<class T>
    class NXS_SHARED common_module : public base_module<T>
    {
    private:
        virtual bool load() override;
        virtual int process(nxs::nex& nex) override;

    protected:
        common_module(int id);
        common_module(const db::line&);
        //common_module(const std::string& name);

    public:
        static void init();
        static int add(const std::string& name, const std::string& ext = "dl");
        static bool load(int id, const std::string& ext);
        template<class M_Type> static bool load(int id);
    };
} // nxs

#include "common.tpp"

#endif // MODULE_COMMON_H_NXS
