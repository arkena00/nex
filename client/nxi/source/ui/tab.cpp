#include <ui/tab.hpp>
#include <ui/main.hpp>
#include <ui/tree.hpp>
#include <ui/tabwidget.hpp>
#include <ui/tabbar.hpp>

#include <QLineEdit>
#include <QDebug>

namespace ui
{
    tab::tab(ui::tabwidget* tabwidget) : QWidget(tabwidget),
        tabwidget_(tabwidget),
        id_((int)reinterpret_cast<void*>(this))
    {
        // link tab widget to tab
        //tabwidget_->tabbar()->setTabData(index, _id);


        // address
        auto address_bar = new QLineEdit(this);
        address_bar->setObjectName("address");
        tabwidget->stack("address")->addWidget(address_bar);
        //QObject::connect(_address_bar, &QLineEdit::returnPressed, this, &tab::address_load);

        // tree
        auto tree = new ui::tree(this);
        tabwidget->stack("tree")->addWidget(tree);
    }

    tab::~tab()
    {
        //window_->client().connexion_delete(_connexion_id);
    }
} // ui
