#include <nxi/page/web.hpp>

#include <nxi/system/page.hpp>

namespace nxi
{
    void web_page::focus()
    {
        page_system_.focus(*this);
    }

    void web_page::load()
    {
        emit event_load();
        page_system_.load(*this);
    }
} // nxi