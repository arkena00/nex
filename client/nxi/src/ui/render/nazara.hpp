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
    class nazara : public render::engine, public Nz::RenderWindow
    {
    private:
        static std::mutex world_lock_;

        QTimer* _timer;
        std::string _data;
        bool _data_loaded;

        Ndk::World _world;
        Ndk::Canvas _canvas;
        Ndk::EntityHandle _model_entity;

        Ndk::TextAreaWidget* _label;

        int _delta;
        QString _text;

        void paintEvent(QPaintEvent*) override;
        QPaintEngine* paintEngine() const override;
        void resizeEvent(QResizeEvent*) override;
        void showEvent(QShowEvent*) override;
        void keyPressEvent(QKeyEvent* ev) override;

    public:
        nazara(QWidget* parent = nullptr);
        ~nazara();

        void load(const std::string&);

        unsigned int GetHeight() const override;
        unsigned int GetWidth() const override;

        virtual QSize sizeHint() const override;

    public slots:
        void update();
    };
}} // ui::render

#endif // UI_RENDER_NAZARA_H_NXI
