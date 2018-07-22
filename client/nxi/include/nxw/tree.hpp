#ifndef NXW_TREE_H_NXI
#define NXW_TREE_H_NXI

namespace ui { class core; }

class QTreeWidget;

#include <QWidget>
#include <ui/interface.hpp>
#include <QTreeWidgetItem>

namespace nxw
{
    class tree_entity : public QTreeWidgetItem
    {
    public:
        tree_entity(tree_entity* parent = nullptr);
    };


    class tree : public ui::interface
    {
    Q_OBJECT
    public:
        tree::tree(ui::core& ui_core);

        void content_interface_set(ui::interface*);

        ui::core& m_ui_core;
        QTreeWidget* m_tree;

        ui::interface* m_content_interface;
    };
} // nxw

#endif // NXW_TREE_H_NXI