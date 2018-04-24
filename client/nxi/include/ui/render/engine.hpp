#ifndef UI_RENDER_ENGINE_H_NXI
#define UI_RENDER_ENGINE_H_NXI

#include <QWidget>

class QString;

namespace ui{namespace render
{
    class page;

    class engine : public QWidget
    {
    Q_OBJECT
    public:
        enum { engine_web, engine_gl };

        engine(QWidget* parent = nullptr) : QWidget(parent) {}

        virtual void load(render::page*) = 0;

        virtual QWidget* widget() = 0;

        virtual void load(const QString&) = 0;
    };
}} // ui::render

#endif // UI_RENDER_ENGINE_H_NXI
