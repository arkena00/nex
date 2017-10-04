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
    class nazara : public engine, Nz::RenderWindow
    {
        Q_OBJECT
    private:
        Ndk::World _world;
        Ndk::Canvas _canvas;
        QTimer* _timer;

    public:
        nazara(QWidget* parent = nullptr);
        ~nazara();

        void load(const QString&);

        void load(render::page*) override {}

        unsigned int GetHeight() const override;
        unsigned int GetWidth() const override;

        QSize sizeHint() const;
        void paintEvent(QPaintEvent*) override;
        QPaintEngine* paintEngine() const override;
        void resizeEvent(QResizeEvent*) override;
        void showEvent(QShowEvent*) override;
        void keyPressEvent(QKeyEvent* ev) override;

        QWidget* widget() override;

    public slots:
        void update();
    };
}} // ui::render

#endif // UI_RENDER_NAZARA_H_NXI
