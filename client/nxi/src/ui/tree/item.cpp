#include "ui/tree/item.hpp"

namespace ui
{
    tree_item::tree_item(tree_item* parent) : QTreeWidgetItem(parent)
    {
        this->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled);
    }

    tree_item::~tree_item()
    {
    }

} // ui
