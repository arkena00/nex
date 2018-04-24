#include <widget/menu.hpp>
#include <widget/menu_action.hpp>

namespace widget
{
    menu::menu(menu* m) : QMenu(m)
    {}

    menu::~menu()
    {
    }

    void menu::add(menu&)
    {

    }

    menu_action* menu::add(const QString& text, menu& menu)
    {
        addMenu(&menu);
        menu_action* action = static_cast<menu_action*>(menu.menuAction());
        action->setText(text);
        return action;
    }

    menu_action* menu::add(const QString& text)
    {
        menu_action* action = new menu_action(this);
        action->setText(text);
        addAction(action);
        return action;
    }

    menu_action* menu::add(const QString& text, const QString& command)
    {
        auto action = add(text);
        action->setData(command);
        return action;
    }

    void menu::on_click(std::function<void(QAction*)> fn)
    {
        QObject::connect(this, &QMenu::triggered, fn);
    }

    void menu::exec()
    {
        QMenu::exec(QCursor::pos());
    }

} // widget