#include <ui/window.hpp>
#include <ui/main.hpp>
#include <ui/render/web.hpp>

#include <nxw/vbox_layout.hpp>

#include <QDesktopWidget>
#include <QIcon>
#include <ui/login.hpp>


namespace ui
{
    window::window(nxi::core& nxi_core) :
        nxi_core_{ nxi_core },
        moving_{ false }
    {
        QIcon icon(":image/nex");
        setWindowIcon(icon);
        setWindowFlags(Qt::CustomizeWindowHint);

        main_layout_ = new nxw::vbox_layout;

        // main window
        QDesktopWidget screen;
        QRect screen_size = screen.availableGeometry(screen.primaryScreen());
        int width = static_cast<int>(screen_size.width() * 0.8);
        int height = static_cast<int>(screen_size.height() * 0.7);
        int x = (screen_size.width() - width) / 2;
        int y = (screen_size.height() - height) / 2;

        // center window
        resize(width, height);
        move(x, y);
        setWindowTitle("nxi");

        // main layout
        setLayout(main_layout_);
    }

    window::~window()
    {
    }

    //! swap main widget of window, restore widgets in layouts on next call
    void window::main_swap(QWidget* new_main, QLayout* origin_layout)
    {
        main_layout_->removeWidget(swapper_current_main_);

        //swapper->swap(new_main, origin_layout)

        // new widget, add it
        if (new_main != swapper_current_main_)
        {
            swapper_origin_layout_ = origin_layout;
            main_layout_->addWidget(new_main);
            swapper_current_main_ = new_main;
        }
        else
        {
            // restore
            swapper_origin_layout_->addWidget(swapper_current_main_);
            main_layout_->addWidget(main_);
            swapper_current_main_ = static_cast<QWidget*>(main_);
        }
    }

    void window::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::RightButton)
        {
            moving_ = true;
            move_origin_ = event->globalPos() - pos();
        }
    }

    void window::mouseReleaseEvent(QMouseEvent* event)
    {
        moving_ = false;
    }

    void window::mouseMoveEvent(QMouseEvent* event)
    {
        QPoint delta = event->globalPos() - move_origin_;
        if (moving_) move(delta.x(), delta.y());
    }

    void window::mouseDoubleClickEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (isMaximized()) showNormal();
            else showMaximized();
        }
    }

    nxi::core& window::nxi_core()
    {
        return nxi_core_;
    }
} // ui
