#include <widget/bar.hpp>

#include <QHBoxLayout>

namespace widget
{
    bar::bar(QWidget* w) : QWidget(w)
    {
        layout_ = new QHBoxLayout(this);
        layout_->setContentsMargins(0, 0, 0, 0);
        layout_->setSpacing(0);
    }

    void bar::add(QWidget* w)
    {
        w->setParent(this);
        layout_->addWidget(w);
    }

} // widget