#include <ui/interface/main.hpp>
#include <ui/interface/control_bar.hpp>

#include <nxw/tree.hpp>
#include <nxw/web_view.hpp>

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace ui::interfaces
{
    main::main(ui::core& ui_core)
    {

        auto main_layout = new QVBoxLayout;
        setLayout(main_layout);

        auto control_bar = new ui::interfaces::control_bar(ui_core);
        m_tree = new nxw::tree(ui_core);
        m_web = new nxw::web_view(ui_core);

        auto top_layout = new QHBoxLayout(this);
        top_layout->addWidget(control_bar);

        auto middle_layout = new QHBoxLayout(this);
        middle_layout->addWidget(m_tree);
        middle_layout->addWidget(m_web);

        main_layout->addLayout(top_layout);
        main_layout->addLayout(middle_layout);

    }

} // ui::interfaces