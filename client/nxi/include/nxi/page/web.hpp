#ifndef NXI_PAGE_WEB_H_NXI
#define NXI_PAGE_WEB_H_NXI

#include <nxi/page.hpp>

namespace nxi
{
    class page_system;

    class web_page : public nxi::page
    {
        Q_OBJECT
    public:
        web_page(nxi::page_system& ps, nxi::page_id id)
            : nxi::page(ps, id, "web_page")
            , url_{ "http://www.google.fr" }
        {}

        void focus();

        const QString& url() const { return url_; }
        void url_update(const QString& url) { url_ = url; }

        static nxi::page_type type() { return page_type::web; }

    private:
        QString url_;

    signals:
        void event_update_icon(const QIcon&);
    };
} // nxi

#endif // NXI_PAGE_WEB_H_NXI
