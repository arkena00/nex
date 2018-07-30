#include <nxw/web_view.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <nxw/web_page.hpp>

#include <QWebEngineView>
#include <QVBoxLayout>

namespace nxw
{
    web_view::web_view(ui::core& ui_core) :
        m_ui_core{ ui_core }
    {
        auto layout = new QVBoxLayout;

        setLayout(layout);

        connect(&m_ui_core.nxi_core().page_system(), &nxi::page_system::event_add,
                [this](nxi::web_page& page)
                {
                    qDebug() << "page add " << page.id;
                    auto ui_page = new nxw::web_page(m_ui_core, page.id, this);
                    m_pages.emplace(page.id, ui_page);
                });


        connect(&m_ui_core.nxi_core().page_system(), &nxi::page_system::event_change, this,
                [this](nxi::web_page& page)
                {
                    m_pages[page.id]->load(QString::fromStdString(page.url));
                    view_->setPage(m_pages[page.id]->native());
                });

        connect(&m_ui_core.nxi_core().page_system(), &nxi::page_system::event_update, this,
                 [this](const nxi::web_page& page)
                 {

                 });

        view_ = new QWebEngineView(this);
        layout->addWidget(view_);

        //view_->setPage()

        m_ui_core.nxi_core().page_system().add({});
    }
}