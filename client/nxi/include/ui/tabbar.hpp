#ifndef UI_TABBAR_H_NXI
#define UI_TABBAR_H_NXI

#include <QTabBar>

namespace ui
{
    class tab;

    class tabbar : public QTabBar
    {
    Q_OBJECT

    private:


    public:
        tabbar(QWidget* widget = nullptr);

        size_t index(tab* t);

        void title_set(tab* t, const QString& text);
    };

} // ui

#endif // UI_TABBAR_H_NXI
