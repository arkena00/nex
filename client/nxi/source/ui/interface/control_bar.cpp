#include <ui/interface/control_bar.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/command.hpp>

#include <QComboBox>
#include <QLineEdit>

#include <nxw/hbox_layout.hpp>
#include <nxw/icon_button.hpp>
#include <nxw/menu.hpp>
#include <include/ui/interface/control_bar.hpp>
#include <ui/web_view.hpp>
#include <QWebEngineView>
#include <include/nxi/module/web.hpp>

namespace nxw
{
    class popup : public QWebEngineView
    {
    public:
        popup(const QString& url)
        {
            load(QUrl::fromLocalFile(url));
        }
    };



class command : public QLineEdit
    {
    public:
        command(ui::core& ui_core) : ui_core_{ ui_core }
        {
            setFixedWidth(400);

            menu_ = new nxw::menu(this);
            menu_->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
            menu_->setFixedWidth(width());
            menu_->hide();

            connect(this, &QLineEdit::editingFinished, [this]()
            {
                menu_->hide();
                menu_->clear();
            });

            connect(this, &QLineEdit::textChanged, [this]()
            {
                menu_->clear();
                auto result = ui_core_.nxi_core().command_system().search(text());
                if (result.size() > 0)
                {
                    for (auto cmd : result)
                    {
                        menu_->add(*cmd);
                    }
                    menu_->show_at(this);
                    menu_->exec();
                }
            });

            connect(&ui_core_.nxi_core().page_system(), qOverload<nxi::page&>(&nxi::page_system::event_focus), this, [this](nxi::page& page)
            {
                setText(page.name());
            });

        }

    private:
        ui::core& ui_core_;

        nxw::menu* menu_;
    };
}


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

        command_bar_ = new nxw::command(m_ui_core);
        QObject::connect(command_bar_, &QLineEdit::returnPressed, [this]()
        {
            nxi::command_context context = nxi::command_context::deduced;
            if (m_context->currentText() == "web") context = nxi::command_context::web;
            if (m_context->currentText() == "explorer") context = nxi::command_context::explorer;

            m_ui_core.nxi_core().command_system().exec(command_bar_->text(), context);
        });


        // module command
        // init
        module_controls_ = new nxw::hbox_layout;
        for (const auto& command : m_ui_core.nxi_core().command_system().get())
        {
            command_add(*command);
        }
        // event
        QObject::connect(&ui_core.nxi_core().command_system(), &nxi::command_system::event_add, [this](const nxi::command& command)
        {
            command_add(command);
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
        layout->addWidget(command_bar_);
        layout->addLayout(module_controls_);
        layout->addStretch();
        layout->addWidget(window_controls);
    }

    void control_bar::command_add(const nxi::command& command)
    {
        auto button = new nxw::icon_button(this, command.icon());
        connect(button, &nxw::icon_button::clicked, [this, &command]()
        {
            /*
            nxi::internal_command
            nxi::web_module_command

            if (command.is_internal()) command.exec();
            if (command.is_webaction())
            {

            }*/

            //
            command.exec();

            /*
            QString path = "C:\\Projet\\nk\\nex\\bin\\nxi\\module\\webextension\\beastify\\popup\\choose_beast.html";
            auto popup = new nxw::popup(path);
            popup->show();*/
        });

        button->setText(command.name());

        //popup->show_at(button);

        module_controls_->addWidget(button);
    }
} // ui::interfaces