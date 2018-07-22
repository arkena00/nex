#ifndef UI_INTERFACE_H_NXI
#define UI_INTERFACE_H_NXI

#include <QStackedWidget>
#include <ui/window.hpp>

namespace ui
{

    class interface : public QWidget
    {
    public:
        interface()
        {
            setWindowFlags(Qt::FramelessWindowHint);
        }

        interface(ui::window* w) : QWidget(w) {}

        void page_add(ui::interface* new_interface)
        {
            pages_->addWidget(new_interface);
        }

        QWidget* widget() { return this; }


        QStackedWidget* pages_;
    };
} // ui

#endif