#ifndef UI_INTERFACE_MAIN_H_NXI
#define UI_INTERFACE_MAIN_H_NXI

#include <ui/interface.hpp>
#include <include/nxw/tree.hpp>

namespace ui::interfaces
{
    class main : public ui::interface
    {
    Q_OBJECT
    public:
        main(ui::core&);

        nxw::tree* m_tree;

    };
} // ui::interfaces

#endif // UI_INTERFACE_MAIN_H_NXI