#ifndef NXW_HBOX_LAYOUT_H_NXI
#define NXW_HBOX_LAYOUT_H_NXI

#include <QHBoxLayout>

namespace nxw
{
    class hbox_layout : public QHBoxLayout
    {
        Q_OBJECT
    public:
        hbox_layout(QWidget* widget = nullptr)
        {
            setContentsMargins(0, 0, 0, 0);
            setSpacing(0);
        }
    };
} // nxw

#endif // NXW_HBOX_LAYOUT_H_NXI
