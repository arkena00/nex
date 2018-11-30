#ifndef UI_RENDERER_WIDGET_H_NXI
#define UI_RENDERER_WIDGET_H_NXI

#include <ui/renderer.hpp>

class QWidget;

namespace ui
{
    class widget_renderer : renderer
    {
    public:
        widget_renderer(QWidget* w);

        void display(widget_page* p);
        QWidget* widget();

        QWidget* widget_;
    };
} // ui

#endif // UI_RENDERER_WIDGET_H_NXI