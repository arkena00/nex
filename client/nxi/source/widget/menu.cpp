#include <widget/menu.hpp>

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

    QAction* menu::add(const QString& text, menu& menu)
    {
        QAction* action = addMenu(&menu);
        action->setText(text);
        return action;
    }

    QAction* menu::add(const QString& text)
    {
        QAction* action = new QAction(this);
        action->setText(text);
        addAction(action);
        return action;
    }

    QAction* menu::add(const QString& text, const QString& command)
    {
        auto action = add(text);
        action->setData(command);
        return action;
    }

    void menu::exec()
    {
        QMenu::exec(QCursor::pos());
    }

} // widget