#ifndef UI_MAIN_H_NXI
#define UI_MAIN_H_NXI

namespace nxi { class core; }
namespace nxw { class vbox_layout; class tabbar; }

class QPushButton;

#include <QWidget>
#include <nxw/tabwidget.hpp>

namespace ui
{
    namespace render { class engine; class web; }

    class window;
    class tabtree;

    class main : public QWidget
    {
        Q_OBJECT
    public:
        main(ui::window* window);
        ~main();

        render::engine* engine();

    public:
        nxi::core& nxi_core_;
        ui::window* window_;

        render::web* engine_web_;

        nxw::vbox_layout* right_layout_;
        nxw::vbox_layout* left_layout_;

        QPushButton* menu_button_;
        nxw::tabwidget* tabwidget_;
        nxw::tabbar* tabbar_;
        ui::tabtree* tabtree_;
    };
} // ui

#endif // UI_MAIN_H_NXI
