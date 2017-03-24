#ifndef UI_RENDER_ENGINE_H_NXI
#define UI_RENDER_ENGINE_H_NXI

#include <QWidget>

namespace ui{namespace render
{
    class engine : public QWidget
    {
    public:
        engine(QWidget* parent = nullptr) : QWidget(parent) {}
        virtual void load(const std::string&) = 0;

    };
}} // ui::render

#endif // UI_RENDER_ENGINE_H_NXI
