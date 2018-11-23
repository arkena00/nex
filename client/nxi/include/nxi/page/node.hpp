#ifndef NXI_PAGE_NODE_H_NXI
#define NXI_PAGE_NODE_H_NXI

#include <nxi/page.hpp>


namespace nxi
{
    class page_system;

    class page_node : public nxi::page
    {
    public:
        page_node(nxi::page_system& ps, nxi::page_id id) : nxi::page(ps, id, "new node") {}
        page_node(nxi::page_system& ps, nxi::page_id id, const QString& name) : nxi::page(ps, id, name) {}

        void focus();

        static nxi::page_type type() { return page_type::node; }

    private:
    };
} // nxi

#endif // NXI_PAGE_NODE_H_NXI