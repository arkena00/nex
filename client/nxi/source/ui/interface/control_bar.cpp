#include <ui/interface/control_bar.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/command.hpp>

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include <nxw/hbox_layout.hpp>

#include <QMenu>

namespace ui::interfaces
{
    control_bar::control_bar(ui::core& ui_core) :
        m_ui_core{ ui_core }
    {
        QHBoxLayout* layout = new nxw::hbox_layout;
        setLayout(layout);

        auto menu_ = new QPushButton(this);
        menu_->setText("menu");

        QMenu* menu = new QMenu(this);
        auto a_quit = new QAction("quit", menu);
        a_quit->setText("quit");

        auto a_win = new QAction(menu);
        a_win->setText("new window");


        QObject::connect(a_quit, &QAction::triggered, [this](){ m_ui_core.quit(); });
        QObject::connect(a_win, &QAction::triggered, [this](){ m_ui_core.nxi_core().window_system().add({}); });

        menu->addAction(a_win);
        menu->addAction(a_quit);

        QObject::connect(menu_, &QPushButton::clicked, this, [menu]{ menu->exec(); });

        m_context = new QComboBox(this);
        m_context->addItem("auto");
        m_context->addItem("web");
        m_context->addItem("explorer");

        m_address_bar = new QLineEdit(this);
        QObject::connect(m_address_bar, &QLineEdit::returnPressed, this, [this]()
        {
            nxi::command_context context = nxi::command_context::deduced;
            if (m_context->currentText() == "web") context = nxi::command_context::web;
            if (m_context->currentText() == "explorer") context = nxi::command_context::explorer;

            m_ui_core.nxi_core().command_system().exec(m_address_bar->text(), context);
        });

        layout->addWidget(menu_);
        layout->addWidget(m_context);
        layout->addWidget(m_address_bar);
    }
} // ui::interfaces