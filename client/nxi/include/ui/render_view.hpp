#ifndef UI_RENDER_VIEW_H_NXI
#define UI_RENDER_VIEW_H_NXI

#include <QWidget>

#include <QWebEngineView>
#include <nxi/page/node.hpp>
#include <nxi/page/web.hpp>
#include <include/nxi/page/custom.hpp>
#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/page.hpp>
#include "web_page.hpp"
#include <ui/system/page.hpp>

namespace ui
{
    class render_engine
    {
        void load(ui::page* page)
        {
            //page->load(*this);
        }
    };



    class web_renderer : QWidget
    {
    Q_OBJECT
    public:
        web_renderer(QWidget* parent) : QWidget(parent)
        {
            view_ = new QWebEngineView(this);
        }

        void load(ui::web_page* page)
        {
            view_->setPage(page->native());
        }

        QWebEngineView* view_;
    };

    class widget_renderer
    {
        void load()
        {

        }
    };

    class render_view : public QWidget
    {
        Q_OBJECT
    public:
        render_view(ui::core& ui_core, QWidget* parent) : QWidget(parent), ui_core_{ui_core}
        {
            web_renderer_ = new web_renderer(this);

            QObject::connect(&ui_core.nxi_core().page_system(), qOverload<nxi::page&>(&nxi::page_system::event_focus), this, [this](nxi::page& page)
            {
                qDebug() << "event_focus " << page.name();
                auto ui_page = ui_core_.page_system().get(page);


                //web_renderer_->load(ui_page);
            });
        }


        void display(nxi::web_page& page)
        {

        }

        void display(nxi::page_node& page)
        {
            //current_widget_ = page->widget();
            //render_engine->load();
        }

        void display(nxi::custom_page& page)
        {
            //current_widget_ = page->widget();
        }

    private:
        QWidget* current_widget_;

        ui::core& ui_core_;

        web_renderer* web_renderer_;

    };

} // nxw

#endif // UI_RENDER_VIEW_H_NXI