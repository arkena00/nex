#ifndef NXI_PAGE_SYSTEM_H_NXI
#define NXI_PAGE_SYSTEM_H_NXI

#include <ui/window.hpp>

#include <QObject>
#include <QDebug>

namespace nxi
{
    enum class page_type { web, explorer, node };

    struct page
    {
        int id;
        std::string name;

        virtual page_type type() = 0;

        page() : id{0} {}
    };

    struct page_node : nxi::page
    {
        int id;

        page_type type() override { return page_type::node; }
    };

    struct web_page : nxi::page
    {
        int id;
        std::string url;

        page_type type() override { return page_type::web; }

        web_page() : id{0}, url{"http://www.google.fr"} {}
    };

    struct explorer_page : nxi::page
    {
        int id;
        std::string path;

        page_type type() override { return page_type::explorer; }

        explorer_page() : id{0}, path{"/"} {}
    };

    class page_system : public QObject
    {
        Q_OBJECT
    public:
        void load();

        void load(nxi::web_page page);

        nxi::page& get(int id);

        //void add(nxi::page page);

        template<class Page>
        void add(Page page)
        {
            auto id = static_cast<int>(page_.size());
            page.id = id;
            auto p = std::make_unique<Page>(std::move(page));

            page_.emplace(id, std::move(p));

            emit event_add(static_cast<Page&>(get(id)));
            //change(page.id);
        }

        void change(int id);

        void update(int id);

        signals:
        //void event_add(nxi::page_node);

        void event_add(nxi::page&);

        void event_add(nxi::web_page&);
        void event_add(nxi::explorer_page&);

        void event_change(nxi::page&);
        void event_change(nxi::web_page&);

        void event_load(nxi::web_page&);

        void event_update(const nxi::page&);
        void event_update(const nxi::web_page&);

    private:
        int m_current_index;
        std::map<int, std::unique_ptr<nxi::page>> page_;
    };
} // nxi

#endif // NXI_PAGE_SYSTEM_H_NXI
/* add
 * load
 * update
 * focus
 *
 *
 */