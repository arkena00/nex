#ifndef NXW_TREE_H_NXI
#define NXW_TREE_H_NXI

namespace ui { class core; }

class QTreeWidget;

#include <ui/interface.hpp>
#include <nxw/tree/page_item.hpp>
#include <include/nxi/system/page.hpp>

namespace ui
{
    class core;
    class tree_item;
    class tree_page_item;

    class page_tree : public QTreeWidget
    {
        Q_OBJECT
    public:
        page_tree::page_tree(ui::core&);

        ui::tree_page_item* add(nxi::page& page, nxi::page_id source_id);
        void add(tree_item*);
        void add(tree_item* item, tree_item* source_item);
        tree_item* get(unsigned int id) const;


        tree_item* current_item() const;

    private:
        ui::core& ui_core_;
        std::unordered_map<nxi::page_id, ui::tree_page_item*> page_items_;
    };
} // nxw

#endif // NXW_TREE_H_NXI