#include <nxw/tabbar.hpp>

namespace nxw
{
    tabbar::tabbar(QWidget* widget) :
        QTabBar(widget)
    {
        setObjectName("tab");
        setTabsClosable(1);
        setMovable(1);
        setDrawBase(0);
    }

} // nxw