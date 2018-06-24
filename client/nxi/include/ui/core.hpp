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

        nxi::core& nxi_core() { return nxi_core_; }

    private:
        nxi::core& nxi_core_;

        std::vector<ui::window*> windows_;

        QSystemTrayIcon* systray_;
    };
} // ui

#endif // UI_CORE_H_NXI
