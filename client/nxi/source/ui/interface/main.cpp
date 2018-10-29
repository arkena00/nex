#include <ui/interface/main.hpp>

#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <nxw/tree.hpp>
#include <nxw/hbox_layout.hpp>
#include <nxw/vbox_layout.hpp>

#include <ui/core.hpp>
#include <ui/interface/content.hpp>
#include <ui/interface/control_bar.hpp>
#include <ui/interface/page_bar.hpp>

namespace ui::interfaces
{
    main::main(ui::core& ui_core) :
        ui_core_{ ui_core }
    {
        auto main_layout = new nxw::vbox_layout;
        setLayout(main_layout);

        auto top_layout = new nxw::hbox_layout(this);
        auto middle_layout = new nxw::hbox_layout(this);

        content_ = new interfaces::content(ui_core_);
        control_bar_ = new ui::interfaces::control_bar(ui_core_);
        page_bar_ = new ui::interfaces::page_bar(ui_core_);

        top_layout->addWidget(control_bar_);

        middle_layout->addWidget(page_bar_);
        middle_layout->addWidget(content_);

        main_layout->addLayout(top_layout);
        main_layout->addLayout(middle_layout);
    }
} // ui::interfaces