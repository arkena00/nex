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
        tab* _tab;

    public:
        tree(tab*);
        ~tree();

        void item_add(tree_item*);
        tree_item* item_add(const QString& name, const QIcon& icon);

    public slots:
        void item_expand(QTreeWidgetItem*);

    };

} // ui

#endif // UI_TREE_H_NXI
