#include <ui/render/web.hpp>
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

    QWidget* web::widget()
    {
        return this;
    }
}} // ui::render