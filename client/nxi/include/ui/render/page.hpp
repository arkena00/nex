#ifndef UI_RENDER_PAGE_H_NXI
#define UI_RENDER_PAGE_H_NXI

#include <QWidget>

class QString;

namespace ui{namespace render
{
    class page : public QWidget
    {
    Q_OBJECT
    public:
        page(QWidget* parent = nullptr) : QWidget(parent) {}

        virtual void load(const QString& data) = 0;

    };
}} // ui::render

#endif // UI_RENDER_PAGE_H_NXI