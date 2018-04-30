#include <ui/tabtree_item.hpp>

#include <nxw/hbox_layout.hpp>

#include <QIcon>
#include <QLabel>

namespace ui
{
    tabtree_item::tabtree_item(QWidget* parent) :
    QWidget(parent)
    {
        icon_ = new QLabel(this);
        icon_->setFixedSize(32, 32);
        icon_->setPixmap(QPixmap(":/image/nex"));

        label_ = new QLabel(this);

        auto main_layout = new nxw::hbox_layout;
        main_layout->addWidget(icon_);
        main_layout->addWidget(label_);

        setFixedHeight(32);

        setLayout(main_layout);
    }

    void tabtree_item::text_set(const QString& text)
    {
        label_->setText(text);
    }

    void tabtree_item::icon_set(const QIcon& icon)
    {
        icon_->setPixmap(icon.pixmap(32, 32));
    }
} // ui
