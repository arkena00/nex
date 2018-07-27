#ifndef NXW_TREE_H_NXI
#define NXW_TREE_H_NXI

namespace ui { class core; }

class QTreeWidget;

#include <QWidget>
#include <ui/interface.hpp>
#include <QTreeWidgetItem>

namespace nxw
{
    class tree_item : public QTreeWidgetItem
    {
    public:
        tree_item(int id, tree_item* parent = nullptr);

        int id() const {return id_;}

    private:
        int id_;
    };


    class tree : public ui::interface
    {
    Q_OBJECT
    public:
        tree::tree(ui::core& ui_core);

        ui::core& m_ui_core;
        QTreeWidget* m_tree;

    };
} // nxw

#endif // NXW_TREE_H_NXI