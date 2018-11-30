#ifndef UI_RENDERER_H_NXI
#define UI_RENDERER_H_NXI

#include <QWidget>

namespace ui
{
    class page;
    class web_page;
    class widget_page;

    class renderer : public QWidget
    {
        Q_OBJECT
    public:
        renderer(const renderer&) = delete;
        renderer& operator=(const renderer&) = delete;

        virtual QWidget* widget() = 0;

        void display(web_page*);
        void display(widget_page*);

        static renderer* make(page*);

    protected:
        renderer() = default;
        virtual ~renderer();
    };
} // ui

#endif // UI_RENDERER_H_NXI