#ifndef NXW_WEB_VIEW_H_NXI
#define NXW_WEB_VIEW_H_NXI

#include <ui/interface.hpp>

#include <unordered_map>
#include <QObject>

class QWebEngineView;
class QWebEnginePage;

namespace ui{ class core; }

namespace nxw
{
    class web_page;

    class web_view : public ui::interface
    {
        Q_OBJECT
    public:
        web_view(ui::core& ui_core);

        QWebEngineView* native();

    private:
        ui::core& ui_core_;
        QWebEngineView* view_;
        std::unordered_map<unsigned int, nxw::web_page*> pages_;
    };
} // nxw

#endif // NXW_WEB_VIEW_H_NXI