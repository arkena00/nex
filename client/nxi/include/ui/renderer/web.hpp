#ifndef UI_RENDERER_WEB_H_NXI
#define UI_RENDERER_WEB_H_NXI

#include <ui/renderer.hpp>

class QWebEngineView;

namespace ui
{
    class web_page;

    class web_renderer : public renderer
    {
    public:
        web_renderer();

        void display(web_page* p);
        QWidget* widget();

    private:
        QWebEngineView* view_;
    };
} // ui

#endif // UI_RENDERER_WEB_H_NXI