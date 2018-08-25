#ifndef UI_INTERFACE_MAIN_H_NXI
#define UI_INTERFACE_MAIN_H_NXI

#include <ui/interface.hpp>

namespace nxw
{
    class tree;
    class web_view;
    class explorer_view;
} // nxw

namespace ui::interfaces
{
    class main : public ui::interface
    {
    Q_OBJECT
    public:
        main(ui::core&);

        ui::core& m_ui_core;
        nxw::tree* m_tree;

        QStackedWidget* m_view;

        nxw::web_view* m_web;
        nxw::explorer_view* m_explorer;
    };
} // ui::interfaces

#endif // UI_INTERFACE_MAIN_H_NXI