#include <ui/tabtree.hpp>

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QModelIndex>
#include <QDebug>

namespace ui
{
    tabtree::tabtree(QWidget* parent) :
        tabchanger(parent)
    {
        tree_ = new QTreeWidget(this);

        connect(tree_, &QTreeWidget::itemClicked, [this](QTreeWidgetItem* item, int)
        {
            QModelIndex index = item->treeWidget()->currentIndex();
            emit tabchanger::event_change(index.row());
        });
    }

    int tabtree::add(const QString& text)
    {
        auto item = new QTreeWidgetItem(tree_);
        item->setText(0, text);
        tree_->addTopLevelItem(item);

        //int index = tabbar_->addTab(text);

        return tree_->topLevelItemCount();
    }

    void tabtree::current_set(int index)
    {
        //tree_->setItemSelected()
        qDebug() << "current_set " << index;
    }

    QWidget* tabtree::widget()
    {
        return tree_;
    }
} // nxw