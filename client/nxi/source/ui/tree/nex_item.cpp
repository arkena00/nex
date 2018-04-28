#include <ui/tree/nex_item.hpp>
#include <ui/tree.hpp>


#include <QDebug>
#include <QTreeWidgetItem>

namespace ui
{
    tree_nex_item::tree_nex_item(ui::tree* tree, size_t id, tree_item* parent) :
        tree_item(tree, parent),
        id_(id)
    {
    }

    tree_nex_item::tree_nex_item(tree_item* parent, size_t id) :
        tree_nex_item(&parent->tree(), id, parent)
    {}

    void tree_nex_item::list()
    {
        tree_item* parent_item = static_cast<tree_item*>(this);
        parent_item->takeChildren();


    }

    void tree_nex_item::option()
    {

    }

    int tree_nex_item::id() const
    {
        return id_;
    }
} // ui