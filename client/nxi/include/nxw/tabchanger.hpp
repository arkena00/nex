#ifndef NXW_TABCHANGER_H_NXI
#define NXW_TABCHANGER_H_NXI

#include <QWidget>

class QString;
class QIcon;

namespace nxw
{
    class tabchanger : public QWidget
    {
        Q_OBJECT
    public:
        tabchanger(QWidget* parent) : QWidget(parent) {}

        virtual int add(const QString& text) = 0;
        virtual void current_set(int index) = 0;
        virtual void icon_set(int index, const QIcon& icon) = 0;
        virtual void title_set(int index, const QString& title) = 0;

    signals:
        void event_change(int index);
    };

} // nxw

#endif // NXW_TABCHANGER_H_NXI
