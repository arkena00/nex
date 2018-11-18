#include <nxw/web_view.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <nxw/vbox_layout.hpp>
#include <nxw/web_page.hpp>

#include <QWebEngineView>

namespace nxw
{
    web_view::web_view(ui::core& ui_core)
        : ui_core_{ ui_core }
    {
        auto layout = new nxw::vbox_layout;
        setLayout(layout);

        // page_system add
        connect(&ui_core_.nxi_core().page_system(), qOverload<nxi::web_page&, nxi::page_id>(&nxi::page_system::event_add),
        [this](nxi::web_page& page, unsigned int)
        {
            auto ui_page = new nxw::web_page(ui_core_, page.id(), this);

            ui_page->load(page.url());
            pages_.emplace(page.id(), std::move(ui_page));
            view_->setPage(pages_[page.id()]->native());

            // ui_core_.nxi_core().page_system().load(page.id);
        });


        // page_system change

        connect(&ui_core_.nxi_core().page_system(), qOverload<nxi::web_page&>(&nxi::page_system::event_change), this,
        [this](nxi::web_page& page)
        {
            view_->setPage(pages_[page.id()]->native());
        });

        // page_system update
        connect(&ui_core_.nxi_core().page_system(), QOverload<const nxi::web_page&>::of(&nxi::page_system::event_update), this,
                 [this](const nxi::web_page& page)
                 {

                 });

        view_ = new QWebEngineView(this);
        layout->addWidget(view_);

    }

    QWebEngineView* web_view::native()
    {
        return view_;
    }
}