#ifndef UI_TREE_ITEM_H_NXI
#define UI_TREE_ITEM_H_NXI

#include <QTreeWidgetItem>
#include <nxs/network/protocol.hpp>

namespace ui
{
    class tree;

    class tree_item : public QTreeWidgetItem
    {
    private:
        ui::tree* tree_;

    public:
        explicit tree_item(ui::tree*, tree_item* parent = 0);
        ~tree_item() = default;

        virtual void list() = 0;
        virtual void option() = 0;

        void node(bool);
        ui::tree& tree();
        nxs::network::protocol& session();
    };
} // ui

#endif // UI_TREE_ITEM_H_NXI
