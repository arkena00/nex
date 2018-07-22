#ifndef NXW_WEB_VIEW_H_NXI
#define NXW_WEB_VIEW_H_NXI

#include <ui/interface.hpp>

class QWebEngineView;

namespace nxw
{
    class web_view : public ui::interface
    {
        Q_OBJECT
    public:
        web_view(ui::core& ui_core);

        QWebEngineView* view_;
    };
} // nxw

#endif // NXW_WEB_VIEW_H_NXI