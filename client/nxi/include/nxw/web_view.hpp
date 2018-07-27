#ifndef NXW_WEB_VIEW_H_NXI
#define NXW_WEB_VIEW_H_NXI

#include <ui/interface.hpp>
#include "web_page.hpp"

class QWebEngineView;
class QWebEnginePage;

namespace ui{ class core; }

namespace nxw
{
    class web_view : public ui::interface
    {
        Q_OBJECT
    public:
        web_view(ui::core& ui_core);

        QWebEngineView* view_;

        ui::core& m_ui_core;

        std::vector<nxw::web_page*> m_pages;
    };
} // nxw

#endif // NXW_WEB_VIEW_H_NXI