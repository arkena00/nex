#ifndef UI_TABDATA_H_NXI
#define UI_TABDATA_H_NXI

#include <nxw/tabdata_base.hpp>

namespace ui
{
    namespace render { class engine; };

    struct tabdata : public nxw::tabdata_base
    {
        render::engine* engine = nullptr;
    };
} // ui

#endif // UI_TABDATA_H_NXI
