#ifndef NXW_TREE_PAGE_ITEM_H_NXI
#define NXW_TREE_PAGE_ITEM_H_NXI

#include <nxw/tree/item.hpp>
#include <include/nxw/tree.hpp>

namespace nxi { class page; }

namespace ui
{
    class page_tree;

    class tree_page_item : public ui::tree_item
    {
    public:
        tree_page_item(ui::page_tree*, nxi::page&, tree_item* parent = nullptr);
        ~tree_page_item() = default;

        nxi::page& page() { return page_; }
        void change() override;
        void list() override {}
        void option() override;

    private:
        ui::page_tree* tree_;
        nxi::page& page_;
    };
} // nxw

#endif // NXW_TREE_PAGE_ITEM_H_NXI
