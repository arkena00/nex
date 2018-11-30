#include <ui/interface/content.hpp>

#include <ui/core.hpp>
#include <nxi/core.hpp>
#include <nxi/system/command.hpp>

#include <nxw/hbox_layout.hpp>
#include <ui/web_view.hpp>
#include <nxw/explorer_view.hpp>

#include <QStackedWidget>
#include <QWebEngineView>

#include <ui/renderer_view.hpp>

namespace ui::interfaces
{
    content::content(ui::core& ui_core) :
        ui_core_{ ui_core }
    {
        QHBoxLayout* layout = new nxw::hbox_layout;
        setLayout(layout);

        render_view_ = new ui::renderer_view(ui_core_, this);

        layout->addWidget(render_view_);

    }
} // ui::interfaces