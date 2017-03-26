#include <ui/render/web.hpp>

namespace ui{namespace render
{
    web::web() : m_view(this->widget())
    {
    }

    void web::load(const QString& data)
    {
        m_view.setHtml(data);
    }

}} // ui::render