#ifndef UI_RENDER_WEB_H_NXI
#define UI_RENDER_WEB_H_NXI

#include <ui/render/engine.hpp>
#include <QWebEngineView>

namespace ui{namespace render
{
    class web : public QWebEngineView, public engine
    {
    public:
        web(QWidget* parent);

        void load(const QString&) override;
        QWidget* widget() override;
    };
}} // ui::render

#endif //UI_RENDER_WEB_H_NXI
