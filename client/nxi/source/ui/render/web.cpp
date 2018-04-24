#include <ui/render/web.hpp>
#include <ui/render/web_page.hpp>

namespace ui{namespace render
{
    web::web(QWidget* parent) : QWebEngineView(parent)
    {
        QWebEngineView::show();
    }

    void web::load(const QString& data)
    {
        setHtml(data);
    }


    void web::load(render::page* page)
    {
        setPage(static_cast<web_page*>(page));
    }

    QWidget* web::widget()
    {
        return static_cast<QWebEngineView*>(this);
    }
}} // ui::render