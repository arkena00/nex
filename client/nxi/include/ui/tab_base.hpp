#ifndef UI_TAB_BASE_H_NXI
#define UI_TAB_BASE_H_NXI

#include <QWidget>

namespace ui
{
    struct tabdata
    {

    };

    class tab_base : public QWidget
    {
    public:
        tab_base(QWidget* parent) : QWidget(parent) {}

        virtual void tab_focus(tabdata* ) = 0;
    };
} // ui

#endif // UI_TAB_BASE_H_NXI
