#ifndef UI_TAB_H_NXI
#define UI_TAB_H_NXI

#include <QWidget>
#include <QDebug>
#include <ui/tab_base.hpp>

class QLineEdit;
class QLabel;
class QWebEnginePage;

namespace nxw { class tabwidget; class hbox_layout; }

namespace ui
{
    class main;
    class tree;
    struct tabdata;

    namespace render { class engine; class page; }

    class tab : public ui::tab_base
    {
    Q_OBJECT

    public:
        ui::main* main_;
        ui::tree* tree_;

        nxw::hbox_layout* engine_layout_;

        void tab_focus(ui::tabdata*) override;
    public:
        tab(ui::main* tabwidget);
        ~tab();

        render::page* page_;

    };

} // ui

#endif // UI_TAB_H_NXI
