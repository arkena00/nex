#include <nxi/system/page.hpp>

#include <nxi/page/node.hpp>
#include <nxi/page/web.hpp>

#include <nxi/database.hpp>

#include <nxi/log.hpp>
#include <nxi/error.hpp>

namespace nxi
{
    void page_system::load()
    {
        nxi_log << "load page_system";

        // load pages
        auto pages = ndb::query<dbs::core>() << (
        ndb::get(nxi_model.page.id, nxi_model.page.name, nxi_model.page.type)
        << ndb::source(nxi_model.page));

        for (auto& page_data : pages)
        {
            std::unique_ptr<nxi::page> page;
            auto page_id = page_data[nxi_model.page.id];
            auto page_type = static_cast<nxi::page_type>(page_data[nxi_model.page.type]);

            // make_page(page_type, args...)
            switch(page_type)
            {
                case page_type::node:
                    internal_add<nxi::page_node>(*this, page_id, page_data[nxi_model.page.name]);

                    break;

                case page_type::web:
                    internal_add<nxi::web_page>(*this, page_id);

                    break;

                case page_type::explorer:
                    //page = std::make_unique<nxi::explorer_page>(*this, page_id);
                    break;

                default:
                    nxi_assert("unknown page type");
            }
        }

        // load page connections
        auto page_connections = ndb::query<dbs::core>() << (
        ndb::get(nxi_model.page_connection.source_id, nxi_model.page_connection.target_id)
        << ndb::source(nxi_model.page_connection));

        for (auto& line : page_connections)
        {
            auto source_id = static_cast<nxi::page_id>(line[nxi_model.page_connection.source_id]);
            auto target_id = static_cast<nxi::page_id>(line[nxi_model.page_connection.target_id]);

            page_connections_.emplace(source_id, target_id);
        }
    }


    void page_system::load(nxi::page_id id)
    {
        /*auto& current_page = static_cast<nxi::web_page&>(page_[m_current_index]);
        current_page.url = page.url;
        emit event_load(current_page);*/
    }

    const page_system::pages_view& page_system::get() const
    {
        return pages_view_;
    }

    const page_system::page_connections_type& page_system::connections() const
    {
        return page_connections_;
    }

    nxi::page& page_system::get(nxi::page_id id) const
    {
        auto page_it = pages_.find(id);
        nxi_assert(page_it != pages_.end());

        return *page_it->second;
    }

    void page_system::focus(nxi::web_page& page) { nxi_log << "FOCUS webpage"; emit event_focus(page); }
    void page_system::focus(nxi::page_node& node) { emit event_focus(node); }

    void page_system::focus(nxi::page_id id)
    {
        nxi_log << "FOCUS " << id;
        current_page_ = &get(id);
        current_page_->focus();
        // emit event_change(static_cast<Page*>(current_page_));
        //emit event_focus(*current_page_);
    }

    void page_system::update(nxi::page_id id)
    {
        //emit event_update(page_.at(id));
    }
} // nxi