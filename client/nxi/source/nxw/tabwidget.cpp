#include <nxw/tabwidget.hpp>

#include <nxi/tabsystem.hpp>
#include <nxw/tabchanger.hpp>
#include <ui/main.hpp>
#include <ui/tab.hpp>

#include <QStackedWidget>

namespace nxw
{
    tabwidget::tabwidget(QWidget* parent, nxi::tabsystem& tabsystem) :
        QWidget(parent),
        tabsystem_{ tabsystem },
        tabdata_{ nullptr }
    {
        tabstack_ = new QStackedWidget(this);

        // connect tabsystem events to widget and tabchangers

        // new tab
        connect(&tabsystem_, &nxi::tabsystem::event_add, [this, parent](QWidget* source, nxi::tab tab)
        {
            if (source == this)
            {
                for (nxw::tabchanger* changer : tabchangers_)
                {
                    changer->add(tab.name);
                }
                auto t = add<ui::tab>(dynamic_cast<ui::main*>(parent));
            }
        });

        // tab changed
        connect(&tabsystem_, &nxi::tabsystem::event_change, [this](QWidget* source, int index)
        {
            if (source == this)
            {
                for (nxw::tabchanger* changer : tabchangers_)
                {
                    changer->current_set(index);
                }
                change(index);
            }
        });
    }

    tabwidget::~tabwidget()
    {
    }

    void tabwidget::tabchanger_add(nxw::tabchanger* tabchanger)
    {
        tabchangers_.push_back(tabchanger);
        connect(tabchanger, &nxw::tabchanger::event_change, [this](int index) { tabsystem_.on_change(this, index); });

    }

    void tabwidget::change(int index)
    {
        tabstack_->setCurrentIndex(index);
        auto w = tabstack_->widget(index);

        static_cast<ui::tab_base*>(w)->tab_focus(tabdata_);
    }

    QWidget* tabwidget::widget()
    {
        return tabstack_;
    }


} // nxw