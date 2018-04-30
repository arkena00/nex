#ifndef UI_TABTREE_ITEM_H_NXI
#define UI_TABTREE_ITEM_H_NXI

#include <QWidget>

class QLabel;

namespace ui
{
    class tabtree_item : public QWidget
    {
    public:
        tabtree_item(QWidget* parent);


        void text_set(const QString&);
        void icon_set(const QIcon&);

    private:
        QLabel* icon_;
        QLabel* label_;
    };

} // ui

#endif // UI_TABTREE_ITEM_H_NXI
