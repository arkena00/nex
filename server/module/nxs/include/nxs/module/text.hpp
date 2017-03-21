#ifndef MODULE_TEXT_H_NXS
#define MODULE_TEXT_H_NXS

#include <nxs/module/base.hpp>

namespace nxs
{
    template<class T>
    class NXS_SHARED text_module : public base_module<T>
    {
    private:
        std::string _text;

    public:
        text_module(int id);

        bool load();
        int process(nxs::nex& nex);
    };
} // nxs

#include "text.tpp"

#endif // MODULE_TEXT_H_NXS
