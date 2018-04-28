#ifndef NXW_TABBAR_H_NXI
#define NXW_TABBAR_H_NXI

#include <QTabBar>

namespace nxw
{
    class tab;

    class tabbar : public QTabBar
    {
    Q_OBJECT

    private:

    public:
        tabbar(QWidget* widget = nullptr);

    };

} // nxw

#endif // NXW_TABBAR_H_NXI
