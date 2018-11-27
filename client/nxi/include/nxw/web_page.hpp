#ifndef NXW_WEB_PAGE_H_NXI
#define NXW_WEB_PAGE_H_NXI

#include <ui/interface.hpp>

#include <nxi/core.hpp>
#include <nxi/system/page.hpp>
#include <nxw/web_view.hpp>
#include <ui/core.hpp>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <nxi/page/web.hpp>
#include <nxi/system/page.hpp>

namespace nxw
{
    class web_page : QObject
    {
        Q_OBJECT
    public:
        web_page(ui::core& ui_core, nxi::web_page& page, nxw::web_view* parent) :
            QObject(parent)
            , page_{ page }
            , ui_core_{ ui_core }
        {
            native_page_ = new QWebEnginePage(this);
            native_page_->settings()->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);

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

            native_page_->settings()->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);
            native_page_->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
        }

        QWebEnginePage* native()
        {
            return native_page_;
        }

        void load_url(const QString& url){}
        void load(const QString& data){ native_page_->load(QUrl(data)); }

    private:
        ui::core& ui_core_;
        nxi::web_page& page_;

        QWebEnginePage* native_page_;
    };

} // nxw

#endif // NXW_WEB_PAGE_H_NXI