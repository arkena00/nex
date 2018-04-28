#ifndef UI_TAB_H_NXI
#define UI_TAB_H_NXI

#include <QWidget>

class QLineEdit;
class QLabel;
class QWebEnginePage;

namespace nxw { class tabwidget; class hbox_layout; }

namespace ui
{
    class main;
    class tree;

    namespace render { class engine; class page; }

    class tab : public QWidget
    {
    Q_OBJECT

    public:
        ui::main* main_;
        ui::tree* tree_;

        nxw::hbox_layout* engine_layout_;

    public:
        tab(ui::main* tabwidget);

        render::page* page_;

    };

} // ui

#endif // UI_TAB_H_NXI
