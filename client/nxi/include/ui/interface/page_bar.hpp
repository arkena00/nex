#ifndef UI_PAGE_BAR_H_NXI
#define UI_PAGE_BAR_H_NXI

#include <ui/window.hpp>
#include <ui/interface.hpp>

namespace nxw { class tree; };

namespace ui::interfaces
{
    class page_bar : public ui::interface
    {
    public:

        explicit page_bar(ui::core& ui_core);

    private:
        ui::core& ui_core_;

        nxw::tree* page_tree_;
    };
} // ui::interfaces

#endif // UI_PAGE_BAR_H_NXI