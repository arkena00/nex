#ifndef WIDGET_MENU_ACTION_H_NXI
#define WIDGET_MENU_ACTION_H_NXI

#include <QAction>

namespace widget
{
    class menu;

    class menu_action : public QAction
    {
    Q_OBJECT

    private:
        std::function<void()> callback_;

    public:
        menu_action(QObject* parent = nullptr);

        void on_trigger(std::function<void()> fn);
    };

} // widget

#endif // WIDGET_MENU_ACTION_H_NXI
