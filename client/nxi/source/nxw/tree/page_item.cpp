#include <nxw/tree/page_item.hpp>

#include <nxi/core.hpp>
#include <nxw/tree.hpp>
#include <ui/core.hpp>
#include <include/nxw/tree/page_item.hpp>


namespace ui
{
    tree_page_item::tree_page_item(ui::page_tree* tree, unsigned int id, tree_item* parent)
        : ui::tree_item(tree, parent)
        , id_{ id }
        , tree_{ tree }
    {
        setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled);
    }

    void tree_page_item::change()
    {

    }

    void tree_page_item::option()
    {

    }
} // nxw
