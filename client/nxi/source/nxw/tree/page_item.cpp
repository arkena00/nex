#include <nxw/tree/page_item.hpp>

#include <nxi/core.hpp>
#include <nxi/page.hpp>
#include <nxw/tree.hpp>
#include <ui/core.hpp>
#include <include/nxw/tree/page_item.hpp>

#include <QWidget>
#include <include/nxw/hbox_layout.hpp>
#include <QtWidgets/QLabel>








namespace ui
{
    tree_page_item::tree_page_item(ui::page_tree* tree, nxi::page& page, tree_item* parent)
        : ui::tree_item(tree, parent)
        , page_{ page }
        , tree_{ tree }
    {
        setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled);

        auto icon = new QLabel;
        icon->setPixmap(QPixmap(":/image/nex").scaledToWidth(16));

        //tree_->setItemDelegate(new CloseButton{});

        /*
        auto layout = new nxw::hbox_layout;
        layout->addWidget(icon);
        layout->addWidget(new QLabel("test"));

        auto page_widget = new QWidget(this);
        page_widget->setLayout(layout);
        page_widget->show();

        tree_->setItemWidget(this, 0, page_widget);*/
    }

    void tree_page_item::change()
    {

    }

    void tree_page_item::option()
    {

    }
} // nxw
