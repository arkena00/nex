#include <ui/renderer.hpp>

#include <ui/renderer/web.hpp>
#include <ui/renderer/widget.hpp>

#include <QDebug>

namespace ui
{
    renderer::~renderer() { qDebug() << "DELETE renderer"; }


    void renderer::display(web_page* p)
    {
        static_cast<web_renderer*>(this)->display(p);
    }

    void renderer::display(widget_page* p)
    {
        static_cast<widget_renderer*>(this)->display(p);
    }

    renderer* renderer::make(page* p)
    {
        return nullptr;//p->renderer_make();
    }
} // ui