#ifndef UI_H_NXI
#define UI_H_NXI

class QApplication;
namespace nxi { class core; }

namespace ui
{
    void load(QApplication& app, nxi::core& nxc);
} // ui

#endif // UI_H_NXI
