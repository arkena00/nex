#ifndef NXW_ICON_BUTTON_H_NXI
#define NXW_ICON_BUTTON_H_NXI

#include <nxi/command.hpp>

#include <QPushButton>

namespace nxw
{
    class icon_button : public QPushButton
    {
        Q_OBJECT
    public:
        icon_button(QWidget* parent, const QString& icon)
        {
            setIcon(QIcon(icon));
            setStyleSheet("QPushButton:hover { border:none; background-color: #DDDDDD; } QPushButton:pressed { border:none; background-color: #BBBBBB; }");
        }
    };
} // nxw

#endif // NXW_ICON_BUTTON_H_NXI