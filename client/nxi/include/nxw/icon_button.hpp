#ifndef NXW_BUTTON_H_NXI
#define NXW_BUTTON_H_NXI

#include <QPushButton>

namespace nxw
{
    class icon_button : public QPushButton
    {
        Q_OBJECT
    public:
        icon_button(QWidget* parent, const QString& icon, int width, int height = 0)
        {
            if (height == 0) height = width;
            setIcon(QIcon(":/button/" + icon));
            setIconSize(QSize(width, height));
            setFixedSize(width, height);
        }
    };
} // nxw

#endif // NXW_BUTTON_H_NXI