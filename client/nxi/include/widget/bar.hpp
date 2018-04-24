#ifndef WIDGET_BAR_H_NXI
#define WIDGET_BAR_H_NXI

#include <QWidget>

class QHBoxLayout;

namespace widget
{
    class bar : public QWidget
    {
    Q_OBJECT

    private:
        QHBoxLayout* layout_;

    public:
        bar(QWidget* w = nullptr);

        void add(QWidget*);
    };

} // widget

#endif // WIDGET_BAR_H_NXI
