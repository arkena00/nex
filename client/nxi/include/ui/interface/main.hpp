#ifndef UI_INTERFACE_MAIN_H_NXI
#define UI_INTERFACE_MAIN_H_NXI

#include <ui/interface.hpp>

namespace nxw
{
    class tree;
    class web_view;
} // nxw

namespace ui::interfaces
{
    class main : public ui::interface
    {
    Q_OBJECT
    public:
        main(ui::core&);

        nxw::tree* m_tree;
        nxw::web_view* m_web;
    };
} // ui::interfaces

#endif // UI_INTERFACE_MAIN_H_NXI