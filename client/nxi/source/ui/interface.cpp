#include <ui/interface.hpp>
#include <include/ui/interface.hpp>


namespace ui
{
    interface::interface()
    {
        setWindowFlags(Qt::FramelessWindowHint);
    }

    interface::interface(ui::window* window) : QWidget(window)
    {}

    ui::window* interface::window() const
    {
        return static_cast<ui::window*>(QWidget::window());
    }

} // ui