#include <ui/renderer_view.hpp>

#include <ui/core.hpp>
#include <ui/system/page.hpp>
#include <nxi/core.hpp>

#include <include/ui/renderer/web.hpp>
#include <ui/page.hpp>
#include <nxw/vbox_layout.hpp>

namespace ui
{
    renderer_view::renderer_view(ui::core& ui_core, QWidget* parent)
        : QWidget(parent)
        , ui_core_{ ui_core }
        , renderer_{ nullptr }
    {
        auto layout = new nxw::vbox_layout;
        setLayout(layout);

        renderer_ = static_cast<renderer*>(new web_renderer);
        layout->addWidget(renderer_->widget());


        QObject::connect(&ui_core.nxi_core().page_system(), qOverload<nxi::page&>(&nxi::page_system::event_focus), this, [this](nxi::page& page)
        {
            qDebug() << "event_focus " << page.name();
            auto ui_page = ui_core_.page_system().get(page);

            display(ui_page);
        });
    }

    void renderer_view::display(ui::page* page)
    {
        //renderer_ = static_cast<renderer*>(new web_renderer);
        //renderer_->display(page);
        page->display(renderer_);
        //page->displayable_with(renderer_);

    }
} // ui

// REPLACE ui::page by nxi::page, get ui_page in renderers