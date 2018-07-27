#ifndef UI_PAGE_SYSTEM_H_NXI
#define UI_PAGE_SYSTEM_H_NXI

#include <ui/window.hpp>
#include <nxw/web_page.hpp>

#include <QObject>

namespace ui
{
    struct web_page
    {
        int id;
        std::string url;
        web_page() : id{0}, url{"http://www.google.fr"} {}
    };

    class page_system : public QObject
    {
        Q_OBJECT
    public:
        page_system(ui::core& ui_core) : m_ui_core{ ui_core }
        {}

        nxw::web_page* add(ui::web_page page)
        {
            auto p = new nxw::web_page;

            m_pages.push_back(p);
            emit event_add(*m_pages.back());
            return p;
        }

        void load()
        {

        }

        nxw::web_page* add()
        {
            auto page = new nxw::web_page;

            return page;
        }

        void change(int index)
        {
            //emit event_change(interface, index);
        }

        signals:
        void event_add(nxw::web_page&);
        void event_change(nxw::web_page&);

    private:
        ui::core& m_ui_core;

        std::vector<nxw::web_page*> m_pages;
    };
} // ui

#endif // UI_PAGE_SYSTEM_H_NXI