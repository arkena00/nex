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

    namespace render { class engine; class web; class nazara; }

    class main : public QWidget
    {
        Q_OBJECT
    private:
        nxi::core& _nxc;

        QPushButton* menu_button_;
        QPushButton* notification_button_;

        ui::tabwidget* tabwidget_;

        render::web* engine_web_;

    public:
        main(ui::window* window);
        ~main();

        nxs::network::client& client();
        ui::tabwidget& tabwidget();
        render::engine& engine();
    };

} // ui

#endif // UI_MAIN_H_NXI
