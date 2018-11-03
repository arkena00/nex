#include <ui/interface/control_bar.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/command.hpp>

#include <QComboBox>
#include <QLineEdit>

#include <nxw/hbox_layout.hpp>
#include <nxw/icon_button.hpp>

#include <QMenu>

namespace ui::interfaces
{
    class window_controls : public ui::interface
    {
    public:
        window_controls::window_controls(ui::core& ui_core)
        {
            auto layout = new nxw::hbox_layout;
            setLayout(layout);

            auto win_minimize = new nxw::icon_button(this, "window_minimize");
            QObject::connect(win_minimize, &QPushButton::pressed, [this, &ui_core]()
            {
                ui_core.window_system().minimize(window());
            });

            auto win_close = new nxw::icon_button(this, "window_close");
            QObject::connect(win_close, &QPushButton::pressed, &ui_core, &ui::core::quit);

            layout->addWidget(win_minimize);
            layout->addWidget(new nxw::icon_button(this, "window_maximize"));
            layout->addWidget(win_close);
        }
    };

    control_bar::control_bar(ui::core& ui_core) :
        m_ui_core{ ui_core }
    {
        QHBoxLayout* layout = new nxw::hbox_layout;
        setLayout(layout);
        setStyleSheet("border-bottom:1px solid #CCCCCC;");

        auto btn_menu = new nxw::icon_button(this, "menu");

        QMenu* menu = new QMenu(this);
        auto a_quit = new QAction("quit", menu);
        a_quit->setText("quit");

        auto a_win = new QAction(menu);
        a_win->setText("new window");


        QObject::connect(a_quit, &QAction::triggered, [this](){ m_ui_core.quit(); });
        QObject::connect(a_win, &QAction::triggered, [this](){ m_ui_core.nxi_core().window_system().add({}); });

        menu->addAction(a_win);
        menu->addAction(a_quit);

        QObject::connect(btn_menu, &QPushButton::clicked, this, [menu]{ menu->exec(); });

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

        auto window_controls = new ui::interfaces::window_controls(ui_core);

        layout->addWidget(btn_menu);
        layout->addSpacing(64);

        layout->addWidget(new nxw::icon_button(this, "history_previous"));
        layout->addWidget(new nxw::icon_button(this, "history_next"));
        layout->addWidget(new nxw::icon_button(this, "notification_none"));
        layout->addWidget(new nxw::icon_button(this, "download"));

        layout->addSpacing(16);
        layout->addWidget(m_context);
        layout->addWidget(m_address_bar);
        layout->addStretch();
        layout->addWidget(window_controls);
    }
} // ui::interfaces