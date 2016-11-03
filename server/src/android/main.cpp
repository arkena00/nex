#include "widget.h"
#include <QApplication>
#include <QTreeWidget>
#include <QTreeWidgetItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QTreeWidget* tree = new QTreeWidget(w);

    QTreeWidgetItem* item = new QTreeWidgetItem(tree);
    item->setText(0, "zeta item");
    tree->addTopLevelItem(item);

    w.show();

    return a.exec();
}
