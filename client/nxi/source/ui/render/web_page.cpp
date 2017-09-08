#include <ui/render/web_page.hpp>

namespace ui{namespace render
{
    web_page::web_page(QWidget* parent) : QWebEnginePage(parent)
    {

    }

    void web_page::load_url(const QString& url)
    {
        setUrl(QUrl(url));
    }

    void web_page::load(const QString& data)
    {
        setHtml(data);
    };
}} // ui::render