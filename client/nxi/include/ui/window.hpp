#ifndef UI_WINDOW_H_NXI
#define UI_WINDOW_H_NXI

#include <nxs/network/client.hpp>
#include <nxi/core.hpp>

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QSystemTrayIcon>

namespace ui
{
    class main;
    class tabbar;

    class window : public QWidget
    {
        Q_OBJECT
    private:
        nxi::core& nxc_;
        ui::main* main_;

        QSystemTrayIcon* systray_;

    public:
        window(nxi::core& nxc);
        ~window();

        nxi::core& nxc();
    };

} // ui

#endif // UI_WINDOW_H_NXI
