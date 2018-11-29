#ifndef UI_WEB_PAGE_H_NXI
#define UI_WEB_PAGE_H_NXI

#include <QObject>
#include <ui/page.hpp>

class QWebEnginePage;

namespace nxi { class web_page; }

namespace ui
{
    class core;
    class web_view;

    class web_page : public ui::page
    {
        Q_OBJECT
    public:
        web_page(ui::core& ui_core, nxi::web_page& page);

        void load(const QString& url);
        QWebEnginePage* native();

    private:
        ui::core& ui_core_;
        nxi::web_page& page_;

        QWebEnginePage* native_page_;
    };

} // nxw

#endif // UI_WEB_PAGE_H_NXI