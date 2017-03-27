#ifndef UI_RENDER_WEB_H_NXI
#define UI_RENDER_WEB_H_NXI

#include <ui/render/engine.hpp>
#include <QWebEngineView>

namespace ui{namespace render
{
    class web : public engine
    {
    private:
        QWebEngineView* m_view;

    public:
        web();
        void load(const QString&) override;

    };
}} // ui::render

#endif //UI_RENDER_WEB_H_NXI
