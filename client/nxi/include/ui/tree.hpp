#ifndef UI_TREE_H_NXI
#define UI_TREE_H_NXI

#include <QTreeWidget>

class QString;
class QIcon;

namespace ui
{
    class tab;
    class tree_item;

    class tree : public QTreeWidget
    {
        Q_OBJECT
    private:
        ui::tab* tab_;

    public:
        tree(tab*);
        ~tree();

        void on_item_expand(QTreeWidgetItem*);
        void on_item_option(const QPoint&);
        void on_connexion_connect();

        void item_add(tree_item*);

        ui::tab& tab();
    };

} // ui

#endif // UI_TREE_H_NXI
