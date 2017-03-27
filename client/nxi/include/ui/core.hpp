#ifndef UI_CORE_H_NXI
#define UI_CORE_H_NXI

#include <ui/main.hpp>

class QApplication;

namespace nxi { class core; }

namespace ui
{
    class core
    {
    private:
        ui::main m_main;

    public:
        core(QApplication& app, nxi::core& nxc);
    };
} // ui

#endif // UI_CORE_H_NXI
