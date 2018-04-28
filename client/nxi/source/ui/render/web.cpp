#include <ui/render/web.hpp>
#include <ui/render/web_page.hpp>

#include <QWebEngineView>

namespace ui::render
{
    web::web(QWidget* parent) : engine(parent)
    {
        view_ = new QWebEngineView(this);
        view_->show();
    }

    void web::load(const QString& data)
    {
        view_->setHtml(data);
    }


    void web::load(render::page* page)
    {
        view_->setPage(static_cast<render::web_page*>(page)->widget());
    }

    QWidget* web::widget()
    {
        return static_cast<QWidget*>(view_);
    }
} // ui::render