#ifndef UI_CONTENT_H_NXI
#define UI_CONTENT_H_NXI

#include <ui/interface.hpp>

namespace nxw
{
    class web_view;
    class explorer_view;
} // nxw

namespace ui { class core; }

class QStackedWidget;

namespace ui::interfaces
{
    class content : public ui::interface
    {
    public:

        explicit content(ui::core& ui_core);

    private:
        ui::core& ui_core_;

        QStackedWidget* view_stack_;

        nxw::web_view* web_view_;
        nxw::explorer_view* explorer_view_;
    };
} // ui::interfaces

#endif // UI_CONTENT_H_NXI