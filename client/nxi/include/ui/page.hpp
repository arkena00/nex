#ifndef UI_PAGE_H_NXI
#define UI_PAGE_H_NXI

#include <QObject>

#include <nxi/page.hpp>

namespace ui
{
    class renderer;

    class page : public QObject
    {
    public:
        page(nxi::page& page) : page_{ page } {}

        virtual void display(renderer*) = 0;
        //virtual renderer* renderer_make() = 0;

        nxi::page& nxi_page() { return page_; }

    private:
        nxi::page& page_;
    };
} // ui

#endif // UI_PAGE_H_NXI