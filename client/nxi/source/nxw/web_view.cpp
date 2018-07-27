#include <nxw/web_view.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <QWebEngineView>
#include <QVBoxLayout>

namespace nxw
{
    web_view::web_view(ui::core& ui_core) : m_ui_core{ ui_core }
    {
        auto layout = new QVBoxLayout;

        setLayout(layout);

        QObject::connect(&m_ui_core.nxi_core().page_system(), &nxi::page_system::event_add,
                [this](nxi::web_page& page)
                {
                    qDebug() << "page add " << page.id;
                    auto ui_page = new nxw::web_page(this);
                    m_pages.push_back(ui_page);

                });
/*
        connect(&ui_core.page_system(), &ui::page_system::event_change, this,
                [](nxw::web_page&)
                {
                    qDebug() << "webview change " ;
                });*/


        view_ = new QWebEngineView(this);
        view_->load(QUrl("http://www.youtube.com"));
        layout->addWidget(view_);

        //view_->setPage()
    }
}