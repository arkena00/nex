#include <ui/window.hpp>
#include <ui/main.hpp>
#include <ui/render/web.hpp>

#include <nxw/vbox_layout.hpp>

#include <QDesktopWidget>
#include <QIcon>
#include <ui/login.hpp>
#include <ui/core.hpp>
#include <nxi/window_system.hpp>


namespace ui
{
    window::window(ui::core& ui_core, ndb::objects::window window_data) :
        ui_core_{ ui_core },
        window_data_{ std::move(window_data) },
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
        if (event->button() == Qt::LeftButton)
        {
            moving_ = true;
            move_origin_ = event->globalPos() - pos();
        }
    }

    void window::mouseReleaseEvent(QMouseEvent* event)
    {
        moving_ = false;
        // save position
        window_data_.x = x();
        window_data_.y = y();
        /*
        ndb::set<nxi::db_main>(nxi_model.window, window_data_);
        ndb::queries::window::save_geometry(x(), y())

        ui_core_.nxi_core().window_system().window(id).position_set(x(), y());*/
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

    void window::closeEvent(QCloseEvent* event)
    {
        /*
        ndb::object_set<nxi::db_main>(window_data);
        db::query() >> ((nxi_model.window.x = x(), nxi_model.window.y = y()) << (nxi_model.window.id == id()));
        ndb::object_del<nxi::db_main>(window_data);
        db::query() - (nxi_model.window.id == id());*/
        deleteLater();
    }

    int64_t window::id() const
    {
        return window_data_.id;
    }

    nxi::core& window::nxi_core()
    {
        return ui_core_.nxi_core();
    }

    ui::window* window::make(ui::core& ui_core, const nxi::window& window_data)
    {
        auto ui_window = new ui::window(ui_core, window_data);
        ui_window->load<ui::main>();
        ui_window->move(window_data.x, window_data.y);
        ui_window->show();
        return ui_window;
    }
} // ui
