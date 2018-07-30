#include <nxw/tree/item.hpp>

namespace nxw
{
    tree_item::tree_item(nxw::tree* tree, tree_item* parent) :
        QTreeWidgetItem(parent)
        , m_tree(tree)
    {
        setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled);
    }
} // nxw
