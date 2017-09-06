#ifndef UI_MAIN_H_NXI
#define UI_MAIN_H_NXI

#include <nxs/network/client.hpp>
#include <nxi/core.hpp>

#include <vector>
#include <memory>

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QSystemTrayIcon>

namespace ui
{
    class window;
    class tabbar;
    class tabwidget;

    class main : public QWidget
    {
        Q_OBJECT
    private:
        nxi::core& _nxc;

        QPushButton* menu_button_;

        ui::tabwidget* tabwidget_;

    public:
        main(ui::window* window);
        ~main();

        nxs::network::client& client();

        ui::tabwidget& tabwidget();
    };

} // ui

#endif // UI_MAIN_H_NXI
