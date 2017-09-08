#include <ui/tabbar.hpp>
#include <ui/tab.hpp>
#include <nxi/error.hpp>

#include <QVariant>
#include <QDebug>

namespace ui
{
    tabbar::tabbar(QWidget* widget) : QTabBar(widget)
    {

    }

    size_t tabbar::index(ui::tab* t)
    {
        for (size_t i = 0; i != count(); i++)
        {
            if (t->id() == tabData(i).value<size_t>()) return i;
        }
        nxi_error << "tabbar index not found" << log::system;
        return 0;
    }

    void tabbar::title_set(tab* t, const QString& text)
    {
        setTabText(index(t), text);
    }

    void tabbar::icon_set(tab* t, const QIcon& icon)
    {
        setTabIcon(index(t), icon);
    }
}