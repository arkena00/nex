#ifndef NXI_PAGE_SYSTEM_H_NXI
#define NXI_PAGE_SYSTEM_H_NXI

#include <nxi/page.hpp>
#include <nxi/page/id.hpp>

#include <QObject>
#include <unordered_map>
#include <stdz/observer_ptr.hpp>

#include <nxi/page/web.hpp>

#include <nxi/database.hpp>

namespace nxi
{
    class page;
    class page_node;
    class web_page;
    class explorer_page;

    class page_system : public QObject
    {
        Q_OBJECT

        using pages_type = std::unordered_map<nxi::page_id, std::unique_ptr<nxi::page>>;
        using pages_view = std::vector<stdz::observer_ptr<nxi::page>>;

        using page_connections_type = std::unordered_multimap<nxi::page_id, nxi::page_id>;

    public:
        void load();

        void load(nxi::page_id page);


        const pages_view& get() const;
        const page_connections_type& connections() const;
        nxi::page& get(nxi::page_id id) const;

        template<class Page>
        void add(nxi::page_id source_id = 0)
        {
            // add page
            ndb::query<dbs::core>() << ndb::add(
                nxi_model.page.name = QString("test")
                , nxi_model.page.type = Page::type()
            );

            auto page_id = static_cast<nxi::page_id>(ndb::last_id<dbs::core>());

            internal_add<Page>(*this, page_id);

            // add connection
            ndb::query<dbs::core>() << ndb::add(
                nxi_model.page_connection.source_id = (int)source_id
                , nxi_model.page_connection.target_id = (int)page_id
            );

            page_connections_.emplace(source_id, page_id);

            emit event_add(static_cast<Page&>(get(page_id)), source_id);
        }

        void focus(nxi::page_id id);

        template<class Page>
        void focus(nxi::page_id id)
        {
            emit event_focus(static_cast<Page&>(get(id)));
            emit event_focus(get(id));
        }

        void focus(nxi::web_page& page);
        void focus(nxi::page_node& node);

        void update(nxi::page_id id);

        signals:
        //void event_add(nxi::page_node);

        void event_add(nxi::page&, nxi::page_id source_id);
        void event_add(nxi::page_node&, nxi::page_id source_id);
        void event_add(nxi::web_page&, nxi::page_id source_id);
        void event_add(nxi::explorer_page&, nxi::page_id source_id);

        void event_focus(nxi::page&);
        void event_focus(nxi::page_node&);
        void event_focus(nxi::web_page&);
        void event_focus(nxi::explorer_page&);

        void event_load(nxi::web_page&);

        void event_update(const nxi::page&);
        void event_update(const nxi::web_page&);

    private:
        template<class Page, class... Args>
        void internal_add(Args&&... args)
        {
            auto page = std::make_unique<Page>(std::forward<Args>(args)...);
            auto page_ptr = stdz::make_observer<nxi::page>(page.get());
            pages_view_.emplace_back(std::move(page_ptr));
            pages_.emplace(page->id(), std::move(page));
        }

        nxi::page* current_page_;
        std::vector<nxi::page*> visible_pages_;

        pages_type pages_;
        pages_view pages_view_;

        page_connections_type page_connections_;
    };
} // nxi

#endif // NXI_PAGE_SYSTEM_H_NXI
/* add / delete
 * load / unload
 * update
 * change
 * show / hide
 *
 */