#ifndef UI_RENDERER_VIEW_H_NXI
#define UI_RENDERER_VIEW_H_NXI

#include <QWidget>

namespace ui
{
    class core;
    class page;
    class renderer;

    class renderer_view : public QWidget
    {
        Q_OBJECT
    public:
        renderer_view(ui::core& ui_core, QWidget* parent);


        void display(page* page);

    private:
        ui::core& ui_core_;
        renderer* renderer_;
    };
} // ui

#endif // UI_RENDERER_VIEW_H_NXI