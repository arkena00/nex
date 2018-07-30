#include <nxw/tree/page_item.hpp>

#include <nxi/core.hpp>
#include <nxw/tree.hpp>
#include <ui/core.hpp>

namespace nxw
{
    tree_page_item::tree_page_item(nxw::tree* tree, int id, tree_item* parent) :
        nxw::tree_item(tree, parent)
        , m_id{ id }
        , m_tree(tree)
    {
        setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled);
    }

    void tree_page_item::load()
    {
        m_tree->ui_core().nxi_core().page_system().change(m_id);
    }
} // nxw
