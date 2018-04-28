#ifndef UI_RENDER_WEB_H_NXI
#define UI_RENDER_WEB_H_NXI

#include <ui/render/engine.hpp>

class QWebEngineView;

namespace ui::render
{
    class web : public engine
    {
        Q_OBJECT
    public:
        web(QWidget* parent);

        void load(const QString&) override;
        void load(render::page*) override;

        QWidget* widget() override;

    private:
        QWebEngineView* view_;
    };
} // ui::render

#endif //UI_RENDER_WEB_H_NXI
