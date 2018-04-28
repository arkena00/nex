#include <nxw/tabwidget.hpp>
#include <QStackedWidget>
#include <nxi/error.hpp>
#include <QLayout>

namespace nxw
{
    tabwidget::tabwidget(QWidget* parent) :
        QWidget(parent)
    {
        tab_stack_ = new QStackedWidget(this);
        current_index_ = 0;
    }

    tabwidget::~tabwidget()
    {
    }



    void tabwidget::on_change(int index)
    {
        qDebug() << "current_index_ index : " << current_index_ << " new index " << index;
        // delete previous index
        if (layout_.count(current_index_))
        {
            qDebug() << "remove current_index_ : " << current_index_;
            layout_[current_index_]->removeWidget(widget_);
        }

        if (layout_.count(index))
        {
            qDebug() << "add new _index_ : " << index;
            layout_[index]->addWidget(widget_);
        }

        stack()->setCurrentIndex(index);

        current_index_ = index;
    }
} // nxw