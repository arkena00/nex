#include <ui/interface/control_bar.hpp>

#include <QLineEdit>
#include <QPushButton>

#include <QHBoxLayout>

namespace ui::interfaces
{
    control_bar::control_bar(ui::core& ui_core) :
        m_ui_core{ ui_core }
    {
        QHBoxLayout* layout = new QHBoxLayout;
        setLayout(layout);

        auto m_menu = new QPushButton(this);
        m_menu->setText("menu");

        m_address_bar = new QLineEdit(this);
        QObject::connect(m_address_bar, &QLineEdit::returnPressed, this, [this]()
        {
            m_address_bar->setText("exec command");
        });

        layout->addWidget(m_menu);
        layout->addWidget(m_address_bar);
    }
} // ui::interfaces