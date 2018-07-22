#include <ui/interface/main.hpp>

#include <nxw/tree.hpp>

namespace ui::interfaces
{
    main::main(ui::core& ui_core)
    {
        m_tree = new nxw::tree(ui_core);

        m_tree->setParent(this);

    }
} // ui::interfaces