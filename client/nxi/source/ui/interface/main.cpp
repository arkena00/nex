#include <ui/interface/main.hpp>
#include <ui/interface/control_bar.hpp>
#include <ui/core.hpp>

#include <nxw/tree.hpp>
#include <nxw/web_view.hpp>

#include <nxw/hbox_layout.hpp>
#include <nxw/vbox_layout.hpp>
#include <nxi/system/page.hpp>
#include <nxi/core.hpp>

#include <QDebug>
#include <nxw/explorer_view.hpp>

namespace ui::interfaces
{
    main::main(ui::core& ui_core) :
        m_ui_core{ ui_core }
    {
        //connect(&ui_core.nxi_core().page_system(), &nxi::page_system::page_load)

        connect(&m_ui_core.nxi_core().page_system(), QOverload<nxi::page&>::of(&nxi::page_system::event_change),
                [this](nxi::page& page)
                {
                    if (page.type() == nxi::page_type::web) m_view->setCurrentIndex(0);
                    if (page.type() == nxi::page_type::explorer) m_view->setCurrentIndex(1);
                    qDebug() << "change render engine " << (int)page.type();
                });

        auto main_layout = new nxw::vbox_layout;
        setLayout(main_layout);

        auto control_bar = new ui::interfaces::control_bar(ui_core);

        m_tree = new nxw::tree(ui_core);

        auto top_layout = new nxw::hbox_layout(this);
        top_layout->addWidget(control_bar);

        m_view = new QStackedWidget(this);
        m_web = new nxw::web_view(ui_core);
        m_explorer = new nxw::explorer_view(ui_core);
        m_view->addWidget(m_web);
        m_view->addWidget(m_explorer);

        auto middle_layout = new nxw::hbox_layout(this);
        middle_layout->addWidget(m_tree);
        middle_layout->addWidget(m_view);

        main_layout->addLayout(top_layout);
        main_layout->addLayout(middle_layout);

    }

} // ui::interfaces