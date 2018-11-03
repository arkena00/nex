#ifndef UI_INTERFACE_H_NXI
#define UI_INTERFACE_H_NXI

#include <ui/window.hpp>

namespace ui
{

    class interface : public QWidget
    {
    public:
        interface();
        interface(ui::window*);

        ui::window* window() const;
    };
} // ui

#endif