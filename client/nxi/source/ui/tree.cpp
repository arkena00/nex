#include "ui/tree.hpp"
#include "ui/tree/item.hpp"
#include "ui/tab.hpp"

#include <nxs/network/client.hpp>
#include <nxs/resource.hpp>

#include <QTabBar>
#include <QHBoxLayout>
#include <QSplitter>
#include <QDebug>

namespace ui
{
    tree::tree(ui::tab* tab) : _tab(tab)
    {
        connect(this, &QTreeWidget::itemExpanded, this, &tree::item_expand);
    }

    tree::~tree() {}

    void tree::item_add(tree_item* item)
    {
        this->addTopLevelItem(item);
    }

    tree_item* tree::item_add(const QString& name, const QIcon& icon)
    {
        tree_item* item = new tree_item;
        item->setText(0, name);
        item->setIcon(0, icon);
        this->addTopLevelItem(item);
        return item;
    }

    void tree::item_expand(QTreeWidgetItem* in_item)
    {
        try
        {
            tree_item *parent_item = static_cast<tree_item *>(in_item);
            parent_item->takeChildren();

            _tab->connexion().protocol().send("nxs::resource_get;", [parent_item, this](nxs::nex& nex)
            {
                std::vector<nxs::resource> res_list = nex.input().data(0).get<std::vector<nxs::resource>>();

                for (auto& res : res_list)
                {
                    tree_item *item = new tree_item(parent_item);
                    item->setText(0, res.name().c_str());
                    parent_item->addChild(item);
                }
            });

        } catch (const std::exception&) { std::cout << "ERROR"; }
    }

} // ui
