#ifndef UI_TREE_NEX_ITEM_H_NXI
#define UI_TREE_NEX_ITEM_H_NXI

#include <ui/tree/item.hpp>

namespace ui
{
    class tree_nex_item : public tree_item
    {
    private:

    public:
        explicit tree_nex_item(ui::tree*, tree_item* parent = 0);
        explicit tree_nex_item(tree_item* parent);
        ~tree_nex_item() = default;

        void list() override;
        void option() override;
    };
} // ui

#endif // UI_TREE_NEX_ITEM_H_NXI
