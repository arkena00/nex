#ifndef NXW_EXPLORER_VIEW_H_NXI
#define NXW_EXPLORER_VIEW_H_NXI

#include <ui/interface.hpp>

#include <QListWidget>

namespace ui{ class core; }

namespace nxw
{
    class explorer_view : public ui::interface
    {
        Q_OBJECT
    public:
        explorer_view(ui::core& ui_core) : m_ui_core{ ui_core }
        {
            list_ = new QListWidget(this);
            list_->addItem("test");
        }


        QListWidget* list_;

        ui::core& m_ui_core;
    };
} // nxw

#endif // NXW_EXPLORER_VIEW_H_NXI