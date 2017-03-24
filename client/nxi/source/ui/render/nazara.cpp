/*


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
#include <Nazara/Utility/Event.hpp>
#include <Nazara/Utility/Keyboard.hpp>

#include <QDebug>
#include <QKeyEvent>

namespace ui{namespace render
{
    std::mutex nazara::world_lock_;

    nazara::nazara(QWidget* parent) : engine(parent),
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


        // world
        _world.GetSystem<Ndk::RenderSystem>().SetGlobalUp(Nz::Vector3f::Down());
        Nz::ColorBackground* bg = new Nz::ColorBackground(Nz::Color(255, 255, 255));
        _world.GetSystem<Ndk::RenderSystem>().SetDefaultBackground(bg);

        // camera
        Ndk::EntityHandle camera = _world.CreateEntity();
        camera->AddComponent<Ndk::NodeComponent>();
        Ndk::CameraComponent& camera_comp = camera->AddComponent<Ndk::CameraComponent>();
        Ndk::NodeComponent& camera_node = camera->AddComponent<Ndk::NodeComponent>();
        camera_comp.SetTarget(this);
        camera_comp.SetProjectionType(Nz::ProjectionType_Orthogonal);

        // light
        Ndk::EntityHandle nebulaLight = _world.CreateEntity();
        Ndk::NodeComponent& nebulaLightNode = nebulaLight->AddComponent<Ndk::NodeComponent>();
        Ndk::LightComponent& nebulaLightComp = nebulaLight->AddComponent<Ndk::LightComponent>(Nz::LightType_Directional);
        nebulaLightNode.SetPosition(0.f, 0.f, 100.f);
        nebulaLightComp.SetColor(Nz::Color(255, 255, 255));
        nebulaLightNode.SetRotation(Nz::EulerAnglesf(0.f, 0.f, 0.f));

        // model
        Nz::ModelRef model = Nz::Model::New();
        model->LoadFromFile("C:\\Projet\\nk\\nex\\client\\win32\\release\\model\\earth.obj");
        _model_entity = _world.CreateEntity();
        _model_entity->AddComponent<Ndk::GraphicsComponent>().Attach(model);
        Ndk::NodeComponent& model_node = _model_entity->AddComponent<Ndk::NodeComponent>();
        model_node.SetPosition(800, 400);
        model_node.Scale(0.2, 0.2, 0.2);


        _canvas.SetSize({(float)GetWidth(), (float)GetHeight()});
        // textarea
        _label = _canvas.Add<Ndk::TextAreaWidget>();
        _label->SetSize({(float)GetWidth(), (float)GetHeight()});
        _label->Center();
        _label->SetText("TEXT AREA");
        _label->EnableBackground(true);
        _label->EnableMultiline();
        _label->SetBackgroundColor(Nz::Color(240, 240, 240));
        _label->SetTextColor(Nz::Color(0, 0, 0));


        Ndk::LabelWidget* test = _canvas.Add<Ndk::LabelWidget>();
        test->Center();
        test->SetBackgroundColor(Nz::Color(200, 200, 200));
        test->SetSize({300.f, 300.f});
        test->UpdateText(Nz::SimpleTextDrawer::Draw("data", 24, Nz::TextStyle_Regular, Nz::Color(0, 0, 0)));
        test->UpdateText(Nz::SimpleTextDrawer::Draw("aze", 24, Nz::TextStyle_Regular, Nz::Color(0, 0, 0)));

    }

    nazara::~nazara()
    {
        _timer->stop();
    }

    void nazara::load(const std::string& data)
    {
        std::lock_guard<std::mutex> lock(world_lock_);
        _data = data;
        _data_loaded = false;
    }


    unsigned int nazara::GetHeight() const { return height(); }
    unsigned int nazara::GetWidth() const { return width(); }

    QSize nazara::sizeHint() const { return QSize(); }
    void nazara::resizeEvent(QResizeEvent*) { OnWindowResized(); }

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

    void nazara::update()
    {
        _delta += 2;
        Ndk::NodeComponent& model_node = _world.GetEntity(_model_entity->GetId())->GetComponent<Ndk::NodeComponent>();
        model_node.SetRotation(Nz::EulerAnglesf(0.f, _delta, 0.f));

        std::lock_guard<std::mutex> lock(world_lock_);
        if (!_data_loaded)
        {
            _label->SetText(_data);
            _data_loaded = true;
        }

        _world.Update(1);
        Display();
    }
}} // ui::render


*/