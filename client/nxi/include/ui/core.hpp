#ifndef UI_CORE_H_NXI
#define UI_CORE_H_NXI

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
        core(const core&) = delete;
        core& operator=(const core&) = delete;

        nxi::core& nxi_core();

    private:
        nxi::core& m_nxi_core;

        QSystemTrayIcon* m_systray;
    };
} // ui

#endif // UI_CORE_H_NXI