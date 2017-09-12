#ifndef UI_TREE_NEX_ITEM_H_NXI
#define UI_TREE_NEX_ITEM_H_NXI

#include <ui/tree/item.hpp>

namespace ui
{
    class tree_nex_item : public tree_item
    {
    private:
        size_t id_;

    public:
        explicit tree_nex_item(ui::tree*, size_t id, tree_item* parent = nullptr);
        explicit tree_nex_item(tree_item* parent, size_t id);
        ~tree_nex_item() = default;

        void list() override;
        void option() override;
    };
} // ui

#endif // UI_TREE_NEX_ITEM_H_NXI
