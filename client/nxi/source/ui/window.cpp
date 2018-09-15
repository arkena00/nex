#include <ui/window.hpp>

#include <ui/core.hpp>
#include <ui/interface.hpp>
#include <ui/system/window.hpp>

#include <nxi/core.hpp>
#include <nxi/database.hpp>

#include <QIcon>
#include <QMouseEvent>
#include <QtWidgets/qboxlayout.h>

#include <nxw/hbox_layout.hpp>
#include <ui/interface/main.hpp>
#include <include/ui/interface/home.hpp>
#include <include/ui/window.hpp>


namespace ui
{
    window::window(ui::core& ui_core, unsigned int id) :
        m_ui_core{ ui_core }
        , m_id{ id }
        , m_moving{ false }
    {
        QIcon icon(":image/nex");
        setWindowIcon(icon);
        setWindowFlags(Qt::CustomizeWindowHint);

        m_layout = new nxw::hbox_layout;
        setLayout(m_layout);
    }

    window::~window(){ }

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
        window_system().move(this, x(), y());
        window_system().resize(this, width(), height());
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
        window_system().close(this);
        deleteLater();
    }

    void window::interface_set(ui::interface* interface)
    {
        m_interface = interface;
        m_interface->setParent(this);
        m_layout->addWidget(m_interface);
    }

    unsigned int window::id() const
    {
        return m_id;
    }

    ui::window_system& window::window_system()
    {
        return m_ui_core.window_system();
    }
} // ui