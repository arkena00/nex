#include <nxw/web_view.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <QWebEngineView>

namespace nxw
{
    web_view::web_view(ui::core& ui_core)
    {
        connect(&ui_core.nxi_core().page_system(), &nxi::page_system::event_add, this,
                [this](ui::interface *ui)
                {
                    qDebug() << ui << "page add ";
                    if (ui == this) qDebug() <<  "page add ";
                });

        connect(&ui_core.nxi_core().page_system(), &nxi::page_system::event_change, this,
                [](ui::interface *ui, int index)
                {
                    qDebug() << "webview change " << index;
                });

        view_ = new QWebEngineView(this);
        view_->load(QUrl("http://www.youtube.com"));
    }
}