
namespace nxi
{
    template<class Page>
    void page_system::add(nxi::page_id source_id)
    {
        // add page
        ndb::query<dbs::core>() << ndb::add(
        nxi_model.page.name = QString("test")
        , nxi_model.page.type = Page::type()
        );

        auto page_id = static_cast<nxi::page_id>(ndb::last_id<dbs::core>());

        // add connection
        ndb::query<dbs::core>() << ndb::add(
        nxi_model.page_connection.source_id = source_id
        , nxi_model.page_connection.target_id = page_id
        );

        //page_connections_.emplace(source_id, page_id);

        internal_add<Page>(source_id, *this, page_id);
    }

    template<class Page, class... Args>
    Page& page_system::internal_add(nxi::page_id source_id, Args&&... args)
    {
        auto page = std::make_unique<Page>(std::forward<Args>(args)...);
        auto page_ptr = stdz::make_observer<nxi::page>(page.get());
        pages_view_.emplace_back(page_ptr);
        pages_.emplace(page->id(), std::move(page));

        emit event_add(static_cast<Page&>(*page_ptr), source_id);
        return static_cast<Page&>(*page_ptr);
    }
} // nxi