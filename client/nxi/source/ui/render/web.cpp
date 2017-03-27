#include <ui/render/web.hpp>
#include <iostream>

namespace ui{namespace render
{
    web::web() : m_view(new QWebEngineView(this))
    {

    }

    void web::load(const QString& data)
    {
        m_view->setHtml(data);
    }

}} // ui::render