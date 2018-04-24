#include <widget/menu_action.hpp>

namespace widget
{
    menu_action::menu_action(QObject* parent) : QAction(parent)
    {}

    void menu_action::on_trigger(std::function<void()> fn)
    {
        callback_ = fn;
        QObject::connect(this, &QAction::triggered, [fn]() { fn(); } );
    }

} // widget