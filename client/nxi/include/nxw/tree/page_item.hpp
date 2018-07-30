#ifndef NXW_TREE_PAGE_ITEM_H_NXI
#define NXW_TREE_PAGE_ITEM_H_NXI

#include <nxw/tree/item.hpp>

namespace nxw
{
    class tree;

    class tree_page_item : public nxw::tree_item
    {
    public:
        tree_page_item(nxw::tree*, int id, tree_item* parent = nullptr);
        ~tree_page_item() = default;


        void load() override;
        void list() override {}
        void option() override {}

    private:
        nxw::tree* m_tree;
        int m_id;
    };
} // nxw

#endif // NXW_TREE_PAGE_ITEM_H_NXI
