#ifndef NXW_TABBAR_H_NXI
#define NXW_TABBAR_H_NXI

#include <nxw/tabchanger.hpp>

#include <QTabBar>

namespace nxw
{
    class tab;

    class tabbar : public tabchanger
    {
        Q_OBJECT
    public:
        tabbar(QWidget* widget = nullptr);

        QWidget* widget();

        int add(const QString& text) override;
        void current_set(int index) override;

    private:
        QTabBar* tabbar_;
    };

} // nxw

#endif // NXW_TABBAR_H_NXI
