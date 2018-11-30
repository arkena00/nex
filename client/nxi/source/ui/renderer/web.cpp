#include <ui/renderer/web.hpp>

#include <ui/page/web.hpp>

#include <QWebEngineView>

namespace ui
{
    web_renderer::web_renderer()
    {
        view_ = new QWebEngineView(this);
    }

    void web_renderer::display(web_page* page)
    {
        view_->setPage(page->native());
    }

    QWidget* web_renderer::widget()
    {
        return view_;
    }

} // ui