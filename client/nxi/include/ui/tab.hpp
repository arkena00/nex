#ifndef UI_TAB_H_NXI
#define UI_TAB_H_NXI

#include <QWidget>

namespace ui
{
    class tabwidget;
    class tree;

    class tab : public QWidget
    {
    Q_OBJECT

    private:
        ui::tabwidget* tabwidget_;
        unsigned int id_;

    public:
        tab(ui::tabwidget* main_widget);
        ~tab();

        void close();
    };

} // ui

#endif // UI_TAB_H_NXI
