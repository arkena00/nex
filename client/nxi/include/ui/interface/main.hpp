#ifndef UI_INTERFACE_MAIN_H_NXI
#define UI_INTERFACE_MAIN_H_NXI

#include <ui/interface.hpp>

namespace ui { class core; }

namespace ui::interfaces
{
    class content;
    class control_bar;
    class page_bar;

    class main : public ui::interface
    {
    Q_OBJECT
    public:
        main(ui::core&);

        ui::core& ui_core_;

        ui::interfaces::content* content_;
        ui::interfaces::page_bar* page_bar_;
        ui::interfaces::control_bar* control_bar_;
    };
} // ui::interfaces

#endif // UI_INTERFACE_MAIN_H_NXI