#ifndef NXW_TAB_BASE_H_NXI
#define NXW_TAB_BASE_H_NXI

#include <QWidget>

namespace nxw
{
    class tab_base : public QWidget
    {
    public:
        tab_base(QWidget* parent) : QWidget(parent) {}

        virtual void on_change() = 0;
    };
} // nxw

#endif // NXW_TAB_BASE_H_NXI
