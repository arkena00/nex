#ifndef NXW_TREE_ITEM_H_NXI
#define NXW_TREE_ITEM_H_NXI

#include <QTreeWidgetItem>

namespace ui
{
    class page_tree;

    class tree_item : public QTreeWidgetItem
    {
    public:
        explicit tree_item(ui::page_tree*, tree_item* parent = 0);
        ~tree_item() = default;


        virtual void change() = 0;
        virtual void list() = 0;
        virtual void option() = 0;

    private:
        ui::page_tree* m_tree;
    };
} // ui

#endif // NXW_TREE_ITEM_H_NXI
