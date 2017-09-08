#ifndef UI_RENDER_NAZARA_H_NXI
#define UI_RENDER_NAZARA_H_NXI

#include <ui/render/engine.hpp>

#include <Nazara/Renderer/RenderWindow.hpp>
#include <Nazara/Graphics.hpp>
#include <NDK/World.hpp>
#include <NDK/Canvas.hpp>
#include <NDK/Widgets/TextAreaWidget.hpp>
#include <mutex>

#include <QWidget>
#include <QTimer>

namespace ui{namespace render
{
    class nazara : public QWidget, Nz::RenderWindow
    {
        Q_OBJECT
    private:
        Ndk::World _world;

    public:
        nazara(QWidget* parent = nullptr);
        ~nazara();

        void load(const QString&);

        QWidget& widget();

    public slots:
        void update();
    };
}} // ui::render

#endif // UI_RENDER_NAZARA_H_NXI
