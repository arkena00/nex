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
    public:
        core(QApplication& app, nxi::core& nxi_core);
        ~core();

    private:
        nxi::core& nxi_core_;

        QSystemTrayIcon* systray_;

    };
} // ui

#endif // UI_CORE_H_NXI
