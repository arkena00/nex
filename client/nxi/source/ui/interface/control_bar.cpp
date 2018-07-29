#include <ui/interface/control_bar.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/command.hpp>

#include <QLineEdit>
#include <QPushButton>

#include <nxw/hbox_layout.hpp>

namespace ui::interfaces
{
    control_bar::control_bar(ui::core& ui_core) :
        m_ui_core{ ui_core }
    {
        QHBoxLayout* layout = new nxw::hbox_layout;
        setLayout(layout);

        auto m_menu = new QPushButton(this);
        m_menu->setText("menu");

        m_address_bar = new QLineEdit(this);
        QObject::connect(m_address_bar, &QLineEdit::returnPressed, this, [this]()
        {
            m_ui_core.nxi_core().command_system().exec(m_address_bar->text());
        });

        layout->addWidget(m_menu);
        layout->addWidget(m_address_bar);
    }
} // ui::interfaces