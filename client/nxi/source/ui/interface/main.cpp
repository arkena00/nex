#include <ui/interface/main.hpp>
#include <ui/interface/control_bar.hpp>

#include <nxw/tree.hpp>
#include <nxw/web_view.hpp>

#include <nxw/hbox_layout.hpp>
#include <nxw/vbox_layout.hpp>
#include <nxi/system/page.hpp>

namespace ui::interfaces
{
    main::main(ui::core& ui_core)
    {
        //connect(&ui_core.nxi_core().page_system(), &nxi::page_system::page_load)

        auto main_layout = new nxw::vbox_layout;
        setLayout(main_layout);

        auto control_bar = new ui::interfaces::control_bar(ui_core);
        m_tree = new nxw::tree(ui_core);
        m_web = new nxw::web_view(ui_core);

        auto top_layout = new nxw::hbox_layout(this);
        top_layout->addWidget(control_bar);

        auto middle_layout = new nxw::hbox_layout(this);
        middle_layout->addWidget(m_tree);
        middle_layout->addWidget((QWidget*)m_web->native());

        main_layout->addLayout(top_layout);
        main_layout->addLayout(middle_layout);

    }

} // ui::interfaces