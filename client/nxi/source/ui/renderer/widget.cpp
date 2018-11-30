#include <ui/renderer/widget.hpp>

#include <QDebug>

namespace ui
{
    widget_renderer::widget_renderer(QWidget* widget) : widget_{ widget }
    {

    }

    void widget_renderer::display(widget_page* p)
    {
        qDebug() << "DISPLAY widget";
    }

    QWidget* widget_renderer::widget()
    {
        return widget_;
    }

} // ui