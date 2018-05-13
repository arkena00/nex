#ifndef UI_TAB_H_NXI
#define UI_TAB_H_NXI

#include <nxw/tab_base.hpp>

namespace nxw { class tabwidget; class hbox_layout; }

namespace ui
{
    class tree;

    namespace render { class engine; class page; }

    class tab : public nxw::tab_base
    {
        Q_OBJECT

    public:
        tab(nxw::tabwidget* tabwidget);
        ~tab();

        void on_change() override;

    private:
        render::engine* engine_;
        nxw::hbox_layout* engine_layout_;
        render::page* engine_page_;

        nxw::tabwidget* tabwidget_;
        ui::tree* tree_;
    };
} // ui

#endif // UI_TAB_H_NXI
