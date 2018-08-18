#ifndef NXW_TREE_H_NXI
#define NXW_TREE_H_NXI

namespace ui { class core; }

class QTreeWidget;

#include <ui/interface.hpp>
#include <nxw/tree/page_item.hpp>

namespace nxw
{
    class tree_item;

    class tree : public ui::interface
    {
        Q_OBJECT
    public:
        tree::tree(ui::core& ui_core);

        void add(tree_item*);

        tree_item* current_item() const;

        ui::core& ui_core() const;

        QTreeWidget* native() { return m_tree; }

    private:
        ui::core& m_ui_core;
        QTreeWidget* m_tree;

        std::unordered_map<int, nxw::tree_page_item*> m_page_items;
    };
} // nxw

#endif // NXW_TREE_H_NXI