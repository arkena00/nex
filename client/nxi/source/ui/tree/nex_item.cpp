#include <ui/tree/nex_item.hpp>
#include <ui/tree.hpp>
#include <ui/tab.hpp>

#include <nxs/network/client.hpp>
#include <nxs/resource.hpp>

#include <QMenu>
#include <QAction>
#include <QDebug>

namespace ui
{
    tree_nex_item::tree_nex_item(ui::tree* tree, tree_item* parent) :
    tree_item(tree, parent)
    {}

    tree_nex_item::tree_nex_item(tree_item* parent) : tree_nex_item(&parent->tree(), parent)
    {}

    void tree_nex_item::list()
    {
        tree_item* parent_item = static_cast<tree_item*>(this);
        parent_item->takeChildren();

        tree().tab().connexion().protocol().send("nxs::resource_get;", [parent_item, this](nxs::nex& nex)
        {
            auto res_list = nex.input().data(0).get<std::vector<nxs::resource>>();

            for (auto& res : res_list)
            {
                tree_nex_item *item = new tree_nex_item(parent_item);
                item->setText(0, res.name().c_str());
                item->setIcon(0, QIcon(":/image/resource"));
                parent_item->addChild(item);
            }
        });
    }

    void tree_nex_item::option()
    {
        QMenu menu;
        QAction action(&menu);
        action.setText("test");
        menu.addAction(&action);

        QObject::connect(&menu, &QMenu::triggered, [](QAction* a)
        {

            qDebug() << "click";
        });
        menu.exec(QCursor::pos());
    }
} // ui