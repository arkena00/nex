#include <ui/system/page.hpp>

#include <nxi/core.hpp>

#include <ui/core.hpp>
#include <ui/page/web.hpp>

#include <QObject>

namespace ui
{

    page_system::page_system(ui::core& ui_core) : ui_core_{ ui_core }
    {
        QObject::connect(&ui_core_.nxi_core().page_system(), qOverload<nxi::web_page&, nxi::page_id>(&nxi::page_system::event_add), this, [this](nxi::web_page& page, nxi::page_id)
        {
            qDebug() << "add ui page" << page.name();
            auto ui_page = new ui::web_page(ui_core_, page);
            add(ui_page);
        });
    }

    void page_system::add(ui::page* ui_page)
    {
        nxi::page_id id = ui_page->nxi_page().id();
        pages_.emplace(id, ui_page);
    }

    ui::page* page_system::get(nxi::page& page)
    {
        return (*pages_.find(page.id())).second;
    }
} // ui