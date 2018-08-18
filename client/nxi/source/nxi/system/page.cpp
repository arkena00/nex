#include <nxi/system/page.hpp>

namespace nxi
{
    void page_system::load()
    {}

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

    /*
    void page_system::add(nxi::page page)
    {

        page.id = static_cast<int>(page_.size());
        page_[page.id] = (page);
        emit event_add(page_.at(page.id));
        change(page.id);
    }*/

    /*
    void page_system::add(nxi::web_page page)
    {
        auto id = static_cast<int>(page_.size());
        auto p = std::make_unique<nxi::web_page>(std::move(page));
        page_.emplace(id, std::move(p));

        emit event_add(static_cast<nxi::web_page&>(*page_.at(id)));
        //change(page.id);
    }*/

    /*
    void page_system::add(nxi::explorer_page page)
    {

    }*/

    void page_system::change(int id)
    {
        /*
        m_current_index = id;
        emit event_change(page_.at(id));*/
    }

    void page_system::update(int id)
    {
        //emit event_update(page_.at(id));
    }
} // nxi