#ifndef UI_CONTROL_BAR_H_NXI
#define UI_CONTROL_BAR_H_NXI

#include <ui/interface.hpp>

namespace nxi { class command; }
namespace nxw { class hbox_layout; class command; }
namespace ui { class core;  }

class QComboBox;
class QLineEdit;
class QPushButton;

namespace ui::interfaces
{
    class control_bar : public ui::interface
    {
    public:

        explicit control_bar(ui::core& ui_core);

        void command_add(const nxi::command&);

    private:
        ui::core& m_ui_core;

        nxw::command* command_bar_;
        QComboBox* m_context;
        nxw::hbox_layout* module_controls_;
    };
} // ui::interfaces

#endif // UI_CONTROL_BAR_H_NXI