#ifndef WIDGET_MENU_H_NXI
#define WIDGET_MENU_H_NXI

#include <QMenu>
#include <widget/menu_action.hpp>

namespace widget
{
    class menu : public QMenu
    {
    Q_OBJECT

    private:

    public:
        menu(menu* = nullptr);
        ~menu();

        void add(menu&);
        menu_action* add(const QString& text, menu&);
        menu_action* add(const QString& text);
        menu_action* add(const QString& text, const QString& command);

        void on_click(std::function<void(QAction*)>);

        void exec();
    };

} // widget

#endif // WIDGET_MENU_H_NXI
