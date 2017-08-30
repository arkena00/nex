#include <ui/tabbar.hpp>
#include <ui/tab.hpp>

#include <QVariant>

namespace ui
{
    tabbar::tabbar(QWidget* widget) : QTabBar(widget)
    {

    }

    size_t tabbar::index(tab* t)
    {
        for (size_t i = 0; i != count(); i++)
        {
            if (t->id() == tabData(i).value<size_t>()) return i;
        }
        nxs_error << "tabbar index not found";
        return 0;
    }

    void tabbar::title_set(tab* t, const QString& text)
    {
        setTabText(index(t), text);
    }
}