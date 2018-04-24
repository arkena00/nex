#include <ui/tabwidget.hpp>
#include <ui/main.hpp>
#include <ui/tab.hpp>
#include <ui/tabbar.hpp>
#include <nxi/error.hpp>

#include <QStackedWidget>
#include <QDebug>

namespace ui
{
    tabwidget::tabwidget(ui::main* m) :
        QWidget(m),
        main_(m)
    {
        tabbar_ = new ui::tabbar(this);
        tabbar_->setObjectName("tab");
        tabbar_->setTabsClosable(1);
        tabbar_->setMovable(1);
        tabbar_->setDrawBase(0);

        QObject::connect(tabbar_, &QTabBar::currentChanged, [&](int index)
        {
            for (auto s : stack_list_) s.second->setCurrentIndex(index);
        });
        QObject::connect(tabbar_, &QTabBar::tabCloseRequested, [&](int index)
        {
            if (tabbar_->count() == 1) return;

            // remove widget in stacks
            for (auto s : stack_list_) delete s.second->widget(index);

            // delete tab before tabbar signal
            tab_list_.erase(tab_list_.begin() + index);

            // remove tab in bar
            tabbar_->removeTab(index);
        });
    }

    tabwidget::~tabwidget()
    {
    }

    void tabwidget::add(const QString& name)
    {
        // wait tab object creation to emit signal
        tabbar_->blockSignals(true);
        tabbar_->addTab(name);

        // create tab
        auto new_tab = std::make_unique<ui::tab>(this);
        tab_list_.push_back(std::move(new_tab));

        auto new_index = tabbar_->count() - 1;
        tabbar_->setTabData(new_index, tab(new_index).id());

        // reactive signal
        tabbar_->blockSignals(false);
        if (new_index == 0) emit tabbar_->currentChanged(new_index);

        // focus new tab
        tabbar_->setCurrentIndex(new_index);
    }

    void tabwidget::stack_add(const std::string& name)
    {
        QStackedWidget* stack = new QStackedWidget(this);
        stack_list_.emplace(name, stack);
    }

    QStackedWidget* tabwidget::stack(const std::string& name)
    {
        if (!stack_list_.count(name)) nxi_error << "tabwidget stack index error" << log::system;
        return stack_list_.at(name);
    }

    ui::tabbar& tabwidget::tabbar()
    {
        return *tabbar_;
    }

    ui::tab& tabwidget::tab(unsigned int index)
    {
        if (index >= tab_list_.size()) nxi_error << "tabwidget tab index error" << log::system;
        return *tab_list_.at(index).get();
    }

    ui::main& tabwidget::main()
    {
        return *main_;
    }
}