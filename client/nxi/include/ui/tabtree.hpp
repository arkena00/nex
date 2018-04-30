#ifndef UI_TABTREE_H_NXI
#define UI_TABTREE_H_NXI

#include <nxw/tabchanger.hpp>

class QTreeWidget;

namespace ui
{
    class tabtree : public nxw::tabchanger
    {
        Q_OBJECT
    public:
        tabtree(QWidget* widget);

        QWidget* widget();

        int add(const QString& text) override;
        void current_set(int index) override;

    private:
        QTreeWidget* tree_;
    };

} // ui

#endif // UI_TABTREE_H_NXI
