#ifndef UI_PAGE_BAR_H_NXI
#define UI_PAGE_BAR_H_NXI

#include <ui/window.hpp>
#include <ui/interface.hpp>
#include <include/nxw/tree/page_item.hpp>
#include <include/nxw/tree.hpp>

namespace nxw { class tree; };
namespace nxi { class web_page; class page_node; };

namespace ui::interfaces
{
    class page_bar : public ui::interface
    {
    public:

        explicit page_bar(ui::core& ui_core);

    private:
        ui::core& ui_core_;
        ui::page_tree* page_tree_;
    };
} // ui::interfaces

#endif // UI_PAGE_BAR_H_NXI