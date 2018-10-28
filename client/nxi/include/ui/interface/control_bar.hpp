#ifndef UI_CONTROL_BAR_H_NXI
#define UI_CONTROL_BAR_H_NXI

#include <ui/interface.hpp>

namespace ui { class core; }

class QComboBox;
class QLineEdit;
class QPushButton;

namespace ui::interfaces
{
    class control_bar : public ui::interface
    {
    public:

        explicit control_bar(ui::core& ui_core);

    private:
        ui::core& m_ui_core;

        QLineEdit* m_address_bar;
        QComboBox* m_context;
    };
} // ui::interfaces

#endif // UI_CONTROL_BAR_H_NXI