#ifndef UI_TREE_ITEM_H_NXI
#define UI_TREE_ITEM_H_NXI

#include <QTreeWidgetItem>

namespace ui
{
    class tree_item : public QTreeWidgetItem
    {
    private:
        int _type;

    public:
        explicit tree_item(tree_item* parent = 0);
        virtual ~tree_item();

    };
} // ui

#endif // UI_TREE_ITEM_H_NXI
