#include <ui/window.hpp>

#include <ui/core.hpp>

#include <nxi/core.hpp>
#include <nxi/database/ui.hpp>
#include <nxi/window_system.hpp>

#include <QIcon>
#include <QMouseEvent>

namespace ui
{
    window::window(ui::core& ui_core) :
        m_ui_core{ ui_core },
        m_moving{ false }
    {
        QIcon icon(":image/nex");
        setWindowIcon(icon);
        setWindowFlags(Qt::CustomizeWindowHint);
    }

    window::~window()
    {
    }

    void window::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            m_moving = true;
            m_move_origin = event->globalPos() - pos();
        }
    }

    void window::mouseReleaseEvent(QMouseEvent* event)
    {
        m_moving = false;
        window_system().position_set(this, x(), y());
    }

    void window::mouseMoveEvent(QMouseEvent* event)
    {
        QPoint delta = event->globalPos() - m_move_origin;
        if (m_moving) move(delta.x(), delta.y());
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
        deleteLater();
    }

    ui::window* window::make(ui::core& ui_core, const nxi::window& window_data)
    {
        auto ui_window = new ui::window(ui_core);
        ui_window->move(window_data.x, window_data.y);
        ui_window->show();
        return ui_window;
    }

    nxi::window_system& window::window_system()
    {
        return m_ui_core.nxi_core().window_system();
    }
} // ui