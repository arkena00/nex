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

namespace nxw
{
    class web_page : QObject
    {
        Q_OBJECT
    public:
        web_page(ui::core& ui_core, int id, nxw::web_view* parent) :
            QObject(parent)
            , m_id{ id }
            , m_ui_core{ ui_core }
        {
            native_page_ = new QWebEnginePage(this);
            connect(native_page_, &QWebEnginePage::urlChanged, this, [this](const QUrl& url)
            {
                auto& page = static_cast<nxi::web_page&>(m_ui_core.nxi_core().page_system().get(m_id));
                page.url_update(url.toString());
            });

            connect(native_page_, &QWebEnginePage::titleChanged, this, [this](const QString& name)
            {
                auto& page = m_ui_core.nxi_core().page_system().get(m_id);
                page.name_update(name);
            });

            connect(native_page_, &QWebEnginePage::iconChanged, this, [this](const QIcon& icon)
            {
                auto& page = static_cast<nxi::web_page&>(m_ui_core.nxi_core().page_system().get(m_id));
                emit page.event_update_icon(icon);
            });

            native_page_->settings()->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);
            native_page_->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
        }

        QWebEnginePage* native()
        {
            return native_page_;
        }

        void load_url(const QString& url){}
        void load(const QString& data){native_page_->setUrl(QUrl(data));}

    private:
        ui::core& m_ui_core;
        int m_id;

        QWebEnginePage* native_page_;
    };

} // nxw

#endif // NXW_WEB_PAGE_H_NXI