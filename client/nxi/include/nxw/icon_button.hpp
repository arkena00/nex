#ifndef NXW_BUTTON_H_NXI
#define NXW_BUTTON_H_NXI

#include <QPushButton>

namespace nxw
{
    class icon_button : public QPushButton
    {
        Q_OBJECT
    public:
        icon_button::icon_button(QWidget* parent, const QString& icon, int size)
        {
            setIcon(QIcon(":/button/" + icon));
            setIconSize(QSize(size, size));
            setFixedSize(size, size);
        }
    };
} // nxw

#endif // NXW_BUTTON_H_NXI