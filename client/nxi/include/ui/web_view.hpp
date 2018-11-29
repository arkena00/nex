#ifndef UI_WEB_VIEW_H_NXI
#define UI_WEB_VIEW_H_NXI

#include <nxi/page/id.hpp>
#include <ui/interface.hpp>

#include <unordered_map>

class QWebEngineView;
class QWebEnginePage;

namespace nxi { class web_page; }

namespace ui
{
    class core;
    class web_page;

    class web_view : public ui::interface
    {
        Q_OBJECT
    public:
        web_view(ui::core& ui_core);

        QWebEngineView* native();

        ui::web_page* get(const nxi::web_page&) const;

    private:
        ui::core& ui_core_;
        QWebEngineView* view_;
        std::unordered_map<nxi::page_id, ui::web_page*> pages_;
    };
} // nxw

#endif // UI_WEB_VIEW_H_NXI