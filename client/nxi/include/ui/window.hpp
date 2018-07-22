#ifndef UI_WINDOW_H_NXI
#define UI_WINDOW_H_NXI

#include <nxi/window.hpp>

#include <QWidget>

class QHBoxLayout;

namespace ui
{
    class core;
    class window_system;
    class interface;

    class window : public QWidget
    {
    Q_OBJECT
    public:
        window(ui::core& ui_core, unsigned int m_id);
        ~window();

        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseDoubleClickEvent(QMouseEvent* event) override;
        void closeEvent(QCloseEvent* event) override;

        void interface_set(ui::interface* interface);

        unsigned int id() const;
        ui::window_system& window_system();

    private:
        ui::core& m_ui_core;
        unsigned int m_id;

        QHBoxLayout* m_layout;

        ui::interface* m_interface;

        bool m_moving;
        QPoint m_move_origin;
    };

} // ui

#endif // UI_WINDOW_H_NXI