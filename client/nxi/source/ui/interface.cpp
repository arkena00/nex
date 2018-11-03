#include <ui/interface.hpp>

namespace ui
{
    interface::interface()
    {
        setWindowFlags(Qt::FramelessWindowHint);
    }

    interface::interface(ui::window* window) : QWidget(window)
    {}

} // ui