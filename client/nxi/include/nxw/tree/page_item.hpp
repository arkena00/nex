#ifndef NXW_TREE_PAGE_ITEM_H_NXI
#define NXW_TREE_PAGE_ITEM_H_NXI

#include <nxw/tree/item.hpp>
#include <include/nxw/tree.hpp>

namespace ui
{
    class page_tree;

    class tree_page_item : public ui::tree_item
    {
    public:
        tree_page_item(ui::page_tree*, unsigned int id, tree_item* parent = nullptr);
        ~tree_page_item() = default;

        int id() const {return id_;}
        void change() override;
        void list() override {}
        void option() override;

    private:
        ui::page_tree* tree_;
        unsigned int id_;
    };
} // nxw

#endif // NXW_TREE_PAGE_ITEM_H_NXI
