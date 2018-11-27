#ifndef NXW_WEB_VIEW_H_NXI
#define NXW_WEB_VIEW_H_NXI

#include <ui/interface.hpp>

#include <unordered_map>
#include <QObject>
#include <nxi/page/id.hpp>

class QWebEngineView;
class QWebEnginePage;

namespace ui{ class core; }
namespace nxi { class web_page; }
namespace nxw { class web_page; }

namespace nxw
{
    class web_page;

    class web_view : public ui::interface
    {
        Q_OBJECT
    public:
        web_view(ui::core& ui_core);

        QWebEngineView* native();

        nxw::web_page* get(const nxi::web_page&) const;

        QWebEnginePage* p1;
        QWebEnginePage* p2;

    private:
        ui::core& ui_core_;
        QWebEngineView* view_;
        std::unordered_map<nxi::page_id, nxw::web_page*> pages_;
    };
} // nxw

#endif // NXW_WEB_VIEW_H_NXI