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

        // load pages, connect all pages to root
        for (auto& page_data : ndb::oget<dbs::core>(nxi_model.page))
        {
            auto page_id = page_data.id;
            auto page_type = page_data.type;

            // make_page(page_type, args...)
            switch(page_type)
            {
                case page_type::node:
                    internal_add<nxi::page_node>(0, *this, page_id, page_data.name);
                    break;

                case page_type::web:
                    internal_add<nxi::web_page>(0, *this, page_id);
                    break;

                case page_type::explorer:
                    //page = std::make_unique<nxi::explorer_page>(*this, page_id);
                    break;

                default:
                    nxi_assert("unknown page type");
            }
        }

        // load page connections, move pages from root to real source
        for (auto& line : ndb::oget<dbs::core>(nxi_model.page_connection))
        {
            //page_connections_.emplace(line.source_id, line.target_id);
            // if source_id == 0, page didn't move
            if (line.source_id != 0) emit event_move(line.target_id, 0, line.source_id);
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

    void page_system::move(nxi::page_id page_id, nxi::page_id source_id, nxi::page_id target_id)
    {
        const auto& pc = nxi_model.page_connection;

        nxi_log << "PS MOVE : " << page_id << source_id << target_id;

        // page doesn't move
        if (source_id == target_id) return;

        ndb::query<dbs::core>() << (
            ndb::set(pc.source_id = target_id, pc.target_id = page_id)
            << ndb::filter(pc.source_id == source_id && pc.target_id == page_id)
        );


        emit event_move(page_id, source_id, target_id);
    }

    void page_system::update(nxi::page_id id)
    {
        //emit event_update(page_.at(id));
    }
} // nxi