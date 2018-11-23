#include <nxi/page/node.hpp>

#include <nxi/system/page.hpp>

namespace nxi
{
    void page_node::focus()
    {
        page_system_.focus(*this);
    }
} // nxi