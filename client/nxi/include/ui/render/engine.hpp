#ifndef UI_RENDER_ENGINE_H_NXI
#define UI_RENDER_ENGINE_H_NXI

#include <QObject>

class QString;

namespace ui{namespace render
{
    class engine : public QObject
    {
        Q_OBJECT
    public:
        engine() = default;

        virtual QWidget* widget() = 0;

    public slots:
        virtual void load(const QString&) = 0;
    };
}} // ui::render

#endif // UI_RENDER_ENGINE_H_NXI
