#include <nxi/system/page.hpp>
#include <nxi/log.hpp>

namespace nxi
{
    void page_system::load()
    {
        nxi_log << "load page_system";
    }

    void page_system::load(nxi::web_page page)
    {
        /*auto& current_page = static_cast<nxi::web_page&>(page_[m_current_index]);
        current_page.url = page.url;
        emit event_load(current_page);*/
    }

    nxi::page& page_system::get(int id)
    {
        return *page_[id];
    }

    void page_system::change(int id)
    {
        m_current_index = id;
        emit event_change(get(id));
    }

    void page_system::update(int id)
    {
        //emit event_update(page_.at(id));
    }
} // nxi