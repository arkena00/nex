#ifndef UI_MAIN_H_NXI
#define UI_MAIN_H_NXI

#include <nxs/network/client.hpp>
#include <nxi/core.hpp>

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QSystemTrayIcon>

class QTabBar;

namespace ui
{
    class main : public QWidget
    {
        Q_OBJECT
    private:
        nxi::core& _nxc;

        QPushButton* _menu_button;
        QTabBar* _tabbar;
        QStackedWidget* _tabstack;
        QSystemTrayIcon* _systray;

    public:
        main(nxi::core &nxc);
        ~main();

        void tab_add(QString name = "nxi");

        nxs::network::client& client();

        QTabBar& tabbar();

    public slots:
        void tab_add_click();
        void tab_close(int index);

    };

} // ui

#endif // UI_MAIN_H_NXI
