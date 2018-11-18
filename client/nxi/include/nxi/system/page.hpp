#ifndef NXI_PAGE_SYSTEM_H_NXI
#define NXI_PAGE_SYSTEM_H_NXI

#include <nxi/page.hpp>
#include <nxi/page/id.hpp>

#include <QObject>
#include <unordered_map>

#include <nxi/page/web.hpp>

#include <nxi/database.hpp>

namespace nxi
{
    class page;
    class page_node;
    //class web_page;
    class explorer_page;


    // page : ID | page_name | page_type
    // page_connection : source_id | target_id


    class page_system : public QObject
    {
        Q_OBJECT

        using pages_type = std::unordered_map<nxi::page_id, std::unique_ptr<nxi::page>>;
        using page_connections_type = std::unordered_map<nxi::page_id, nxi::page_id>;

    public:
        void load();

        void load(nxi::page_id page);


        const pages_type& get() const;
        const page_connections_type& connection_get() const;
        nxi::page& get(nxi::page_id id) const;

        template<class Page>
        void add(nxi::page_id source_id = 0)
        {
            ndb::query<dbs::core>() << ndb::add(
                nxi_model.page.name = QString("test")
                , nxi_model.page.type = (int)Page::type()
            );

            auto page_id = static_cast<nxi::page_id>(ndb::last_id<dbs::core>());

            auto page = std::make_unique<Page>(*this, page_id);

            pages_.emplace(page_id, std::move(page));
            page_connections_.emplace(source_id, page_id);

            emit event_add(static_cast<Page&>(get(page_id)), source_id);
            //change(page.id);
        }

        void change(nxi::page_id id);

        template<class Page>
        void change(nxi::page_id id)
        {
            emit event_change(static_cast<Page&>(get(id)));
            emit event_change(get(id));
        }

        void change(nxi::web_page& page);
        void change(nxi::page_node& node);

        void update(nxi::page_id id);

        signals:
        //void event_add(nxi::page_node);

        void event_add(nxi::page&, nxi::page_id source_id);
        void event_add(nxi::page_node&, nxi::page_id source_id);
        void event_add(nxi::web_page&, nxi::page_id source_id);
        void event_add(nxi::explorer_page&, nxi::page_id source_id);

        void event_change(nxi::page&);
        void event_change(nxi::page_node&);
        void event_change(nxi::web_page&);
        void event_change(nxi::explorer_page&);

        void event_load(nxi::web_page&);

        void event_update(const nxi::page&);
        void event_update(const nxi::web_page&);

    private:
        nxi::page* current_page_;
        std::vector<nxi::page*> visible_pages_;

        pages_type pages_;
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