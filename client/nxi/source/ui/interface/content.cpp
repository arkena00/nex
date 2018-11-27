#include <ui/interface/content.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/command.hpp>

#include <nxw/hbox_layout.hpp>
#include <nxw/web_view.hpp>
#include <nxw/explorer_view.hpp>

#include <QStackedWidget>
#include <QWebEngineView>

namespace ui::interfaces
{
    content::content(ui::core& ui_core) :
        ui_core_{ ui_core }
    {
        QHBoxLayout* layout = new nxw::hbox_layout;
        setLayout(layout);

        view_stack_ = new QStackedWidget(this);
        web_view_ = new nxw::web_view(ui_core_);
        explorer_view_ = new nxw::explorer_view(ui_core_);

        view_stack_->addWidget(web_view_);
        view_stack_->addWidget(explorer_view_);

        layout->addWidget(view_stack_);

        view_stack_->setCurrentIndex(0);

        /*
        // interface_system::event_view_change
        connect(&ui_core_.nxi_core().page_system(), QOverload<nxi::web_page&>::of(&nxi::page_system::event_focus),
                [this](nxi::web_page& page)
                {
                    view_stack_->setCurrentIndex(0);
                });

        connect(&ui_core_.nxi_core().page_system(), QOverload<nxi::custom_page&>::of(&nxi::page_system::event_focus),
                [this](nxi::custom_page& page)
                {
                    view_stack_->setCurrentIndex(2);
                });
                */
    }
} // ui::interfaces