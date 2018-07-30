#ifndef NXW_TREE_ITEM_H_NXI
#define NXW_TREE_ITEM_H_NXI

#include <QTreeWidgetItem>

namespace nxw
{
    class tree;

    class tree_item : public QTreeWidgetItem
    {
    public:
        explicit tree_item(nxw::tree*, tree_item* parent = 0);
        ~tree_item() = default;

        virtual void load() = 0;
        virtual void list() = 0;
        virtual void option() = 0;

    private:
        nxw::tree* m_tree;
    };
} // ui

#endif // NXW_TREE_ITEM_H_NXI
