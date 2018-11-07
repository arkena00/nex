#include <ui/interface/control_bar.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/command.hpp>

#include <QComboBox>
#include <QLineEdit>

#include <nxw/hbox_layout.hpp>
#include <nxw/icon_button.hpp>
#include <nxw/menu.hpp>

namespace ui::interfaces
{
    class window_controls : public ui::interface
    {
    public:
        window_controls::window_controls(ui::core& ui_core)
        {
            auto layout = new nxw::hbox_layout;
            setLayout(layout);

            auto win_minimize = new nxw::icon_button(this, ":/button/window_minimize");
            QObject::connect(win_minimize, &QPushButton::pressed, [this, &ui_core]()
            {
                ui_core.window_system().minimize(window());
            });

            auto win_close = new nxw::icon_button(this, ":/button/window_close");
            QObject::connect(win_close, &QPushButton::pressed, &ui_core, &ui::core::quit);

            layout->addWidget(win_minimize);
            layout->addWidget(new nxw::icon_button(this, ":/button/window_maximize"));
            layout->addWidget(win_close);
        }
    };

    control_bar::control_bar(ui::core& ui_core) :
        m_ui_core{ ui_core }
    {
        QHBoxLayout* layout = new nxw::hbox_layout;
        setLayout(layout);
        setStyleSheet("border-bottom:1px solid #CCCCCC;");

        auto btn_menu = new nxw::icon_button(this, ":/button/menu");

        /*
        class command
        {
        private:
            QString module_;
            QString name_;
            nxi::shortcut shortcut_;
            std::function<void(ui::core&)> function_;
        };

        nxi::quit
        nxi:shortcuts


        nxi::command cmd("nxi", "quit", [this](){ m_ui_core.quit(););
        cmd.desc_set("desc");
        cmd.shortcut_set(nxi::shortcut());
*/

        auto menu = new nxw::menu{ this };
        menu->setObjectName("main_menu");
        menu->add<nxw::menu_item>("new window", [&ui_core](){ ui_core.nxi_core().window_system().add({}); });
        menu->add<nxw::menu_item>("options");
        menu->add<nxw::menu_item>("about");
        menu->add<nxw::menu_separator>();
        menu->add(ui_core.nxi_core().command_system().get("quit"));
        menu->show_at(btn_menu);

        QObject::connect(btn_menu, &nxw::icon_button::clicked, menu, &nxw::menu::exec);
        //menu->add(nxi::command::get("nxi", "quit"), customwidget);


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


        // module command
        auto module_controls = new nxw::hbox_layout;
        for (const auto& command : m_ui_core.nxi_core().command_system().get())
        {
            auto button = new nxw::icon_button(this, command);
            button->setText(command.command_name());
            module_controls->addWidget(button);
        }
        QObject::connect(&ui_core.nxi_core().command_system(), &nxi::command_system::event_add, [&](const nxi::command& command)
        {
            auto button = new nxw::icon_button(this, command);
            button->setText(command.command_name());
            module_controls->addWidget(button);
        });


        auto window_controls = new ui::interfaces::window_controls(ui_core);

        layout->addWidget(btn_menu);
        layout->addSpacing(64);

        layout->addWidget(new nxw::icon_button(this, ":/button/history_previous"));
        layout->addWidget(new nxw::icon_button(this, ":/button/history_next"));
        layout->addWidget(new nxw::icon_button(this, ":/button/notification_none"));
        layout->addWidget(new nxw::icon_button(this, ":/button/download"));

        layout->addSpacing(16);
        layout->addWidget(m_context);
        layout->addWidget(m_address_bar);
        layout->addLayout(module_controls);
        layout->addStretch();
        layout->addWidget(window_controls);
    }
} // ui::interfaces