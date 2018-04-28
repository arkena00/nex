#ifndef UI_CORE_H_NXI
#define UI_CORE_H_NXI

#include <ui/window.hpp>

class QApplication;
class QSystemTrayIcon;

namespace nxi { class core; }

namespace ui
{
    class core
    {
    private:
        ui::window window_;
        QSystemTrayIcon* systray_;

    public:
        core(QApplication& app, nxi::core& nxi_core);
    };
} // ui

#endif // UI_CORE_H_NXI
