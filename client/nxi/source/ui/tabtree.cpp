#include <ui/tabtree.hpp>

#include <ui/tabtree_item.hpp>

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QModelIndex>
#include <QDebug>
#include <QLineEdit>

namespace ui
{
    tabtree::tabtree(QWidget* parent) :
        tabchanger(parent)
    {
        tree_ = new QTreeWidget(this);
        tree_->setHeaderHidden(1);
        tree_->setStyleSheet("border: none;");
        tree_->setRootIsDecorated(false);
        tree_->setContextMenuPolicy(Qt::CustomContextMenu);
        tree_->setEditTriggers(QAbstractItemView::EditKeyPressed);
        tree_->setFixedWidth(200);

        tree_->setDragEnabled(1);
        tree_->setAcceptDrops(1);
        tree_->setDropIndicatorShown(1);
        tree_->setDragDropMode(QAbstractItemView::DragDrop);
        tree_->setDefaultDropAction(Qt::MoveAction);

        // on click > tab change
        connect(tree_, &QTreeWidget::itemClicked, [this](QTreeWidgetItem* item, int)
        {
            QModelIndex index = item->treeWidget()->currentIndex();
            emit tabchanger::event_change(index.row());
        });
    }

    int tabtree::add(const QString& text)
    {
        auto item = new QTreeWidgetItem(tree_);
        tree_->addTopLevelItem(item);

        auto item_widget = new tabtree_item(this);
        item_widget->text_set(text);

        tree_->setItemWidget(item, 0, item_widget);

        return tree_->topLevelItemCount();
    }

    void tabtree::current_set(int index)
    {
        //tree_->setItemSelected()
        qDebug() << "current_set " << index;
    }

    void tabtree::icon_set(int index, const QIcon& icon)
    {
        auto item = tree_->topLevelItem(index);
        auto widget = tree_->itemWidget(item, 0);
        static_cast<tabtree_item*>(widget)->icon_set(icon);
    }

    void tabtree::title_set(int index, const QString& title)
    {
        auto item = tree_->topLevelItem(index);
        auto widget = tree_->itemWidget(item, 0);
        static_cast<tabtree_item*>(widget)->text_set(title);
    }

    QWidget* tabtree::widget()
    {
        return tree_;
    }
} // nxw