#include <nxw/web_view.hpp>

#include <nxw/web_page.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <nxw/vbox_layout.hpp>
#include <nxw/web_page.hpp>

#include <QWebEngineView>
#include <include/nxi/error.hpp>

namespace nxw
{
    web_view::web_view(ui::core& ui_core)
        : ui_core_{ ui_core }
    {
        auto layout = new nxw::vbox_layout;
        setLayout(layout);

        // page_system add
        connect(&ui_core_.nxi_core().page_system(), qOverload<nxi::web_page&, nxi::page_id>(&nxi::page_system::event_add),
        [this](nxi::web_page& page, nxi::page_id)
        {
            auto ui_page = new nxw::web_page(ui_core_, page, this);
            ui_page->load(page.url());

            qDebug() << "event_add " << page.id();
            pages_.emplace(page.id(), ui_page);
            //view_->setPage(get(page)->native());

            qDebug() << "event_add";
            // load the page on add
            //page.load();
        });



        // page_system change

        connect(&ui_core_.nxi_core().page_system(), qOverload<nxi::web_page&>(&nxi::page_system::event_focus), this,
        [this](nxi::web_page& page)
        {
            qDebug() << "event_focus " << page.id() <<  p1 << "-" << p2;
            view_->setPage(get(page)->native());

        });



        view_ = new QWebEngineView(this);
        layout->addWidget(view_);
    }

    nxw::web_page* web_view::get(const nxi::web_page& page) const
    {
        auto page_it = pages_.find(page.id());
        nxi_assert(page_it != pages_.end());
        return page_it->second;
    }

    QWebEngineView* web_view::native()
    {
        return view_;
    }
}