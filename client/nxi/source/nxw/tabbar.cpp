#include <nxw/tabbar.hpp>

#include <QTabBar>

namespace nxw
{
    tabbar::tabbar(QWidget* parent) :
        tabchanger(parent)
    {
        tabbar_ = new QTabBar(this);

        tabbar_->setObjectName("tab");
        tabbar_->setTabsClosable(1);
        tabbar_->setMovable(1);
        tabbar_->setDrawBase(0);

        connect(tabbar_, &QTabBar::currentChanged, [this](int index) { emit tabchanger::event_change(index); });
    }

    int tabbar::add(const QString& text)
    {
        // block Qt signals
        blockSignals(true);
        int index = tabbar_->addTab(text);
        blockSignals(false);
        return index;
    }

    void tabbar::current_set(int index)
    {
        // block Qt signals
        blockSignals(true);
        tabbar_->setCurrentIndex(index);
        blockSignals(false);
    }

    void tabbar::icon_set(int index, const QIcon& icon)
    {
        tabbar_->setTabIcon(index, icon);
    }

    void tabbar::title_set(int index, const QString& title)
    {
        tabbar_->setTabText(index, title);
    }

    QWidget* tabbar::widget()
    {
        return tabbar_;
    }
} // nxw