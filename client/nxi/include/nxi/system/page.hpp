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
        {}

        void load(nxi::web_page page)
        {
            auto& current_page = page_[m_current_index];
            current_page.url = page.url;
            emit event_load(current_page);
        }

        nxi::web_page& get(int id)
        {
            return page_[id];
        }

        void add(nxi::web_page page)
        {
            page.id = static_cast<int>(page_.size());
            page_[page.id] = (page);
            emit event_add(page_.at(page.id));
            change(page.id);
        }

        void change(int id)
        {
            m_current_index = id;
            emit event_change(page_.at(id));
        }

        void update(int id)
        {
            emit event_update(page_.at(id));
        }

        signals:
        void event_add(nxi::web_page&);
        void event_change(nxi::web_page&);
        void event_load(nxi::web_page&);
        void event_update(const nxi::web_page&);

    private:
        int m_current_index;
        std::map<int, nxi::web_page> page_;
    };
} // nxi

#endif // NXI_PAGE_SYSTEM_H_NXI