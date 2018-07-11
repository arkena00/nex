#ifndef UI_WINDOW_H_NXI
#define UI_WINDOW_H_NXI

namespace ndb::objects { struct window; };
namespace nxi { class core; class window_system; }

#include <QWidget>

namespace nxi
{
    using window = ndb::objects::window;
} // nxi

namespace ui
{
    class core;
    class main;

    class window : public QWidget
    {
    Q_OBJECT
    public:
        window(ui::core& ui_core);
        ~window();

        nxi::window_system& window_system();

        void mousePressEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseDoubleClickEvent(QMouseEvent* event) override;

        void closeEvent(QCloseEvent* event) override;

        static ui::window* make(ui::core& ui_core, const ndb::objects::window& window);

    private:
        ui::core& m_ui_core;

        bool m_moving;
        QPoint m_move_origin;
    };

} // ui

#endif // UI_WINDOW_H_NXI