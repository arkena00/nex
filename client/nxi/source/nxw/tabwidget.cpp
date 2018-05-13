#include <nxw/tabwidget.hpp>

#include <nxi/tabsystem.hpp>
#include <nxw/tabchanger.hpp>
#include <nxw/tabdata_base.hpp>
#include <ui/main.hpp>
#include <ui/tab.hpp>

#include <QStackedWidget>

namespace nxw
{
    tabwidget::tabwidget(QWidget* parent, nxi::tabsystem& tabsystem) :
        QWidget(parent),
        tabsystem_{ tabsystem }
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
                // add tab in stack
                auto new_tab = add<ui::tab>(this);
                // change to new tab
                tabsystem_.on_change(source, index(new_tab));
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

    void tabwidget::change(int index)
    {
        tabstack_->setCurrentIndex(index);
        auto current_tab = tabstack_->widget(index);

        static_cast<nxw::tab_base*>(current_tab)->on_change();
    }

    void tabwidget::data_add(std::unique_ptr<nxw::tabdata_base> tabdata)
    {
        tabdata_ = std::move(tabdata);
    }

    void tabwidget::tabchanger_add(nxw::tabchanger* tabchanger)
    {
        tabchangers_.push_back(tabchanger);
        connect(tabchanger, &nxw::tabchanger::event_change, [this](int index) { tabsystem_.on_change(this, index); });

    }

    void tabwidget::icon_set(int index, const QIcon& icon)
    {
        for (nxw::tabchanger* changer : tabchangers_)
        {
            changer->icon_set(index, icon);
        }
    }

    void tabwidget::icon_set(nxw::tab_base* tab, const QIcon& icon)
    {
        icon_set(index(tab), icon);
    }

    void tabwidget::title_set(int index, const QString& title)
    {
        for (nxw::tabchanger* changer : tabchangers_)
        {
            changer->title_set(index, title);
        }
    }

    void tabwidget::title_set(nxw::tab_base* tab, const QString& title)
    {
        title_set(index(tab), title);
    }

    int tabwidget::index(nxw::tab_base* tab) const
    {
        return tabstack_->indexOf(tab);
    }

    const nxw::tabdata_base& tabwidget::tabdata() const
    {
        return *tabdata_;
    }

    QWidget* tabwidget::widget()
    {
        return tabstack_;
    }
} // nxw