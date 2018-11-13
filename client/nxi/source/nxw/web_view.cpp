#include <nxw/web_view.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <nxw/vbox_layout.hpp>
#include <nxw/web_page.hpp>

#include <QWebEngineView>

namespace nxw
{
    web_view::web_view(ui::core& ui_core) :
        m_ui_core{ ui_core }
    {
        auto layout = new nxw::vbox_layout;
        setLayout(layout);

        // page_system add

        connect(&m_ui_core.nxi_core().page_system(), qOverload<nxi::web_page&, unsigned int>(&nxi::page_system::event_add),
                [this](nxi::web_page& page, unsigned int)
                {
                    auto ui_page = new nxw::web_page(m_ui_core, page.id(), this);

                    ui_page->load(page.url());
                    m_pages.emplace(page.id(), std::move(ui_page));
                    view_->setPage(m_pages[page.id()]->native());

                    // m_ui_core.nxi_core().page_system().load(page.id);
                });


        // page_system change

        connect(&m_ui_core.nxi_core().page_system(), &nxi::page_system::event_change, this,
                [this](nxi::page& page)
                {
                    //m_pages[page.id]->load(QString::fromStdString(page.url));
                    //view_->setPage(m_pages[page.id]->native());
                    view_->load(QUrl(page.name()));
                });

        // page_system update
        connect(&m_ui_core.nxi_core().page_system(), QOverload<const nxi::web_page&>::of(&nxi::page_system::event_update), this,
                 [this](const nxi::web_page& page)
                 {

                 });

        view_ = new QWebEngineView(this);
        layout->addWidget(view_);

        //view_->setPage()

        m_ui_core.nxi_core().page_system().add<nxi::web_page>();
    }

    QWebEngineView* web_view::native()
    {
        return view_;
    }
}