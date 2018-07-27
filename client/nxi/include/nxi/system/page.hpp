#ifndef NXI_PAGE_SYSTEM_H_NXI
#define NXI_PAGE_SYSTEM_H_NXI

#include <ui/window.hpp>

#include <QObject>

namespace nxi
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
        void load()
        {

        }

        void add(nxi::web_page page)
        {
            page.id = page_.size();
            page_.push_back(std::move(page));
            emit event_add(page_.back());
        }

        void change(int index)
        {
            emit event_change(page_.at(index));
        }

        signals:
        void event_add(nxi::web_page&);
        void event_change(nxi::web_page&);

    private:
        std::vector<nxi::web_page> page_;
    };
} // nxi

#endif // NXI_PAGE_SYSTEM_H_NXI