#ifndef UI_CORE_H_NXI
#define UI_CORE_H_NXI

#include <ui/system/window.hpp>
#include <ui/system/page.hpp>

namespace nxi { class core; }

class QApplication;
class QSystemTrayIcon;

namespace ui
{
    class window_system;

    class core
    {
    public:
        core(QApplication& app, nxi::core& nxi_core);
        ~core() = default;
        core(const core&) = delete;
        core& operator=(const core&) = delete;

        void load();
        void quit() const;

        nxi::core& nxi_core();
        ui::window_system& window_system();
        ui::page_system& page_system();

    private:
        QApplication& m_app;
        nxi::core& m_nxi_core;

        ui::window_system m_window_system;
        ui::page_system m_page_system;

        QSystemTrayIcon* m_systray;
    };
} // ui

#endif // UI_CORE_H_NXI