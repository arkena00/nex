#ifndef WIDGET_MENU_H_NXI
#define WIDGET_MENU_H_NXI

#include <QMenu>

class QAction;

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
        QAction* add(const QString& text, menu&);
        QAction* add(const QString& text);
        QAction* add(const QString& text, const QString& command);

        void exec();
    };

} // widget

#endif // WIDGET_MENU_H_NXI
