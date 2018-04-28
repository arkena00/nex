#include <ui/render/web_page.hpp>

#include <QWebEnginePage>

namespace ui::render
{
    web_page::web_page(QWidget* parent) :
        render::page(parent)
    {
        page_ = new QWebEnginePage(this);
    }

    void web_page::load_url(const QString& url)
    {
        page_->setUrl(QUrl(url));
    }

    void web_page::load(const QString& data)
    {
        page_->setUrl(QUrl(data));
        //page_->setHtml(data);
    };

    QWebEnginePage* web_page::widget()
    {
        return page_;
    }
} // ui::render