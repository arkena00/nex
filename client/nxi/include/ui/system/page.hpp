#ifndef UI_SYSTEM_PAGE_H_NXI
#define UI_SYSTEM_PAGE_H_NXI

#include <nxi/type.hpp>

#include <unordered_map>

#include <QObject>

namespace nxi { class page; }

namespace ui
{
    class core;
    class page;

    class page_system : public QObject
    {
        Q_OBJECT
    public:
        page_system(ui::core& ui_core);

        void add(ui::page* ui_page);

        ui::page* get(nxi::page& page);

    private:
		ui::core& ui_core_;

        std::unordered_map<nxi::page_id, ui::page*> pages_;
    };
} // ui

#endif // UI_SYSTEM_PAGE_H_NXI