#ifndef UI_WINDOW_H_NXI
#define UI_WINDOW_H_NXI

namespace nxi { class core; }
namespace nxw { class vbox_layout; }

#include <QLayout>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <utility>

#include <nxw/vbox_layout.hpp>

namespace ui
{
    class main;

    class window : public QWidget
    {
        Q_OBJECT
    public:
        window(nxi::core& nxi_core);
        ~window();

        void main_swap(QWidget* new_main, QLayout* origin_layout_);

        template<class T>
        T* load()
        {
            auto t = new T(this);
            main_layout_->addWidget(t);
            return t;
        }

        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        void mouseDoubleClickEvent(QMouseEvent* event);

        nxi::core& nxi_core();

    private:
        nxi::core& nxi_core_;

        QWidget* main_;

        bool moving_;
        QPoint move_origin_;

        QWidget* swapper_current_main_;
        QLayout* swapper_origin_layout_;
        nxw::vbox_layout* main_layout_;
    };

} // ui

#endif // UI_WINDOW_H_NXI
