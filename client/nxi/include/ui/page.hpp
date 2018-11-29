#ifndef UI_PAGE_H_NXI
#define UI_PAGE_H_NXI

#include <QObject>

#include <nxi/page.hpp>

namespace ui
{

    class page : public QObject
    {

    public:
        page(nxi::page& page) : page_{ page } {}

        nxi::page& nxi_page() { return page_; }

    private:
        nxi::page& page_;

    };
} // ui

#endif // UI_PAGE_H_NXI