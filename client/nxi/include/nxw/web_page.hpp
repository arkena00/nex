#ifndef NXW_WEB_PAGE_H_NXI
#define NXW_WEB_PAGE_H_NXI

#include <ui/interface.hpp>

#include <nxi/core.hpp>
#include <nxi/system/page.hpp>
#include <nxw/web_view.hpp>
#include <ui/core.hpp>
#include <QWebEnginePage>

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
            page_ = new QWebEnginePage(this);
            connect(page_, &QWebEnginePage::urlChanged, this, [this](const QUrl& url)
            {
                auto& page = static_cast<nxi::web_page&>(m_ui_core.nxi_core().page_system().get(m_id));
                page.url = url.toString().toStdString();
                m_ui_core.nxi_core().page_system().update(page.id);
            });
        }

        QWebEnginePage* native()
        {
            return page_;
        }

        void load_url(const QString& url){}
        void load(const QString& data){page_->setUrl(QUrl(data));}

    private:
        ui::core& m_ui_core;
        int m_id;

        QWebEnginePage* page_;
    };

} // nxw

#endif // NXW_WEB_PAGE_H_NXI