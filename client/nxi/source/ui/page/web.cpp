#include <ui/page/web.hpp>

#include <nxi/page/web.hpp>
#include <ui/renderer.hpp>

#include <QWebEnginePage>
#include <QWebEngineSettings>

namespace ui
{
    web_page::web_page(ui::core& ui_core, nxi::web_page& page) :
        ui::page{ page }
        , page_{ page }
        , ui_core_{ ui_core }
    {
        native_page_ = new QWebEnginePage(this);
        native_page_->settings()->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);
        native_page_->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);

        connect(native_page_, &QWebEnginePage::urlChanged, this, [this](const QUrl& url)
        {
            page_.url_update(url.toString());
        });

        connect(native_page_, &QWebEnginePage::loadFinished, this, [this](bool n)
        {
            qDebug() << "COMPELTE " << n;
        });

        connect(native_page_, &QWebEnginePage::titleChanged, this, [this](const QString& name)
        {
            page_.name_update(name);
        });

        connect(native_page_, &QWebEnginePage::iconChanged, this, [this](const QIcon& icon)
        {
            emit page_.event_update_icon(icon);
        });



        connect(&page_, &nxi::web_page::event_load, this, [this]()
        {
            qDebug() << "LOAD PAGE";
            native_page_->load(QUrl(page_.url()));
        });
    }

    void web_page::display(ui::renderer* renderer)
    {
        qDebug() << "web_page::display " << page_.url();
        native_page_->load(QUrl(page_.url()));
        renderer->display(this);
    }

    void web_page::load(const QString& url)
    {
        native_page_->load(QUrl(url));
    }

    QWebEnginePage* web_page::native()
    {
        return native_page_;
    }
} // ui