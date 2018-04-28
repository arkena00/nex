#ifndef NXW_VBOX_LAYOUT_H_NXI
#define NXW_VBOX_LAYOUT_H_NXI

#include <QVBoxLayout>

namespace nxw
{
    class vbox_layout : public QVBoxLayout
    {
    Q_OBJECT
    public:
        vbox_layout(QWidget* widget = nullptr)
        {
            setContentsMargins(0, 0, 0, 0);
            setSpacing(0);
        }
    };
} // nxw

#endif // NXW_VBOX_LAYOUT_H_NXI
