#ifndef UI_TABWIDGET_H_NXI
#define UI_TABWIDGET_H_NXI

#include <QVector>
#include <memory>

#include <QWidget>
#include <unordered_map>

class QStackedWidget;

namespace ui
{
    class main;
    class tab;
    class tabbar;

    class tabwidget : public QWidget
    {
    Q_OBJECT

    private:
        std::vector<std::unique_ptr<ui::tab>> tab_list_;
        std::unordered_map<std::string, QStackedWidget*> stack_list_;

        ui::main* main_;
        ui::tabbar* tabbar_;

    public:
        tabwidget(ui::main*);
        ~tabwidget();

        void add(const QString& name = "nxi");
        void stack_add(const std::string& name);

        QStackedWidget* stack(const std::string& name);
        ui::tabbar& tabbar();
        ui::tab& tab(unsigned int index);
        ui::main& main();
    };
} // ui

#endif // UI_TABWIDGET_H_NXI