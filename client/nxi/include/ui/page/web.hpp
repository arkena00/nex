#ifndef UI_PAGE_WEB_H_NXI
#define UI_PAGE_WEB_H_NXI

#include <ui/page.hpp>

class QWebEnginePage;

namespace nxi { class web_page; }

namespace ui
{
    class core;

    class web_page : public ui::page
    {
        Q_OBJECT
    public:
        web_page(ui::core& ui_core, nxi::web_page& page);

        void display(renderer*) override;

        void load(const QString& url);
        QWebEnginePage* native();

    private:
        ui::core& ui_core_;
        nxi::web_page& page_;

        QWebEnginePage* native_page_;
    };

} // nxw

#endif // UI_PAGE_WEB_H_NXI