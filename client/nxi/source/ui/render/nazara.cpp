#include <ui/render/nazara.hpp>
#include <NDK/Systems/RenderSystem.hpp>
#include <NDK/Components/CameraComponent.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/LightComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Utility.hpp>
#include <NDK/Widgets/TextAreaWidget.hpp>
#include <NDK/Widgets/LabelWidget.hpp>
#include <NDK/Canvas.hpp>
#include <Nazara/Platform/Event.hpp>
#include <Nazara/Platform/Keyboard.hpp>

#include <QDebug>
#include <QKeyEvent>

namespace ui{namespace render
{

    nazara::nazara(QWidget* parent) :
        _canvas(_world.CreateHandle(), GetEventHandler(), GetCursorController().CreateHandle())
    {
        // Setup some states to allow direct rendering into the widget
        setAttribute(Qt::WA_PaintOnScreen);
        setAttribute(Qt::WA_OpaquePaintEvent);
        setAttribute(Qt::WA_NoSystemBackground);

        // Set strong focus to enable keyboard events to be received
        setFocusPolicy(Qt::StrongFocus);
        setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

        if (!IsValid())
        {
            #ifdef Q_WS_X11
            XFlush(QX11Info::display());
            #endif

            Nz::RenderWindow::Create(reinterpret_cast<Nz::WindowHandle>(winId()));
            SetEventListener(true);
            SetCursor(Nz::Cursor::Get(Nz::SystemCursor_Default));
        }


        _timer = new QTimer(this);
        _timer->setInterval(10);
        QObject::connect(_timer, &QTimer::timeout, this, &nazara::update);

        _canvas.SetSize({(float)GetWidth(), (float)GetHeight()});
        // textarea
        auto _label = _canvas.Add<Ndk::TextAreaWidget>();
        _label->SetSize({(float)GetWidth(), (float)GetHeight()});
        _label->Center();
        _label->SetText("TEXT AREA");
        _label->EnableBackground(true);
        _label->EnableMultiline();
        _label->SetBackgroundColor(Nz::Color(255, 255, 255));
        _label->SetTextColor(Nz::Color(0, 0, 0));


        // world
        _world.GetSystem<Ndk::RenderSystem>().SetGlobalUp(Nz::Vector3f::Down());
        Nz::ColorBackground* bg = new Nz::ColorBackground(Nz::Color(255, 255, 255));
        _world.GetSystem<Ndk::RenderSystem>().SetDefaultBackground(bg);

        // light
        Ndk::EntityHandle nebulaLight = _world.CreateEntity();
        Ndk::NodeComponent& nebulaLightNode = nebulaLight->AddComponent<Ndk::NodeComponent>();
        Ndk::LightComponent& nebulaLightComp = nebulaLight->AddComponent<Ndk::LightComponent>(Nz::LightType_Directional);
        nebulaLightNode.SetPosition(0.f, 0.f, 500.f);
        nebulaLightComp.SetColor(Nz::Color(255, 255, 255));

        // model
        Nz::ModelRef model = Nz::Model::New();
        model->LoadFromFile(R"(C:\Projet\nk\nex\client\nxi\bin\resources\test\test.obj)");
        auto _model_entity = _world.CreateEntity();
        _model_entity->AddComponent<Ndk::GraphicsComponent>().Attach(model);
        Ndk::NodeComponent& model_node = _model_entity->AddComponent<Ndk::NodeComponent>();
        model_node.SetPosition(500, 200, -50);
        model_node.SetScale(2.f);

        // camera
        Ndk::EntityHandle camera = _world.CreateEntity();
        camera->AddComponent<Ndk::NodeComponent>();
        Ndk::CameraComponent& camera_comp = camera->AddComponent<Ndk::CameraComponent>();
        Ndk::NodeComponent& camera_node = camera->AddComponent<Ndk::NodeComponent>();
        camera_comp.SetTarget(this);
        camera_comp.SetProjectionType(Nz::ProjectionType_Orthogonal);

    }

    nazara::~nazara()
    {
        _timer->stop();
    }

    void nazara::load(const QString& data)
    {

    }


    void nazara::update()
    {
        _world.Update(1);
        Display();

    }

    unsigned int nazara::GetHeight() const { return height(); }
    unsigned int nazara::GetWidth() const { return width(); }

    QSize nazara::sizeHint() const { return QSize{}; }
    void nazara::resizeEvent(QResizeEvent*){ OnWindowResized(); }

    void nazara::showEvent(QShowEvent*)
    {
        _timer->start();
    }

    QPaintEngine* nazara::paintEngine() const { return nullptr; }

    void nazara::paintEvent(QPaintEvent*){}

    void nazara::keyPressEvent(QKeyEvent* ev)
    {
    if (ev->text().size() == 0) return;
    Nz::WindowEvent e;
    e.type = Nz:: WindowEventType_TextEntered;
    e.text.character= ev->text().toStdU32String().at(0);
    GetEventHandler().Dispatch(e);

    }

    QWidget* nazara::widget()
    {
        return this;
    }
}} // ui::render
