#include <nxi/page.hpp>

#include <nxi/database.hpp>

namespace nxi
{
    page::page(page_system& ps, nxi::page_id id, const QString& name)
        : page_system_{ ps }
        , id_{ id }
        , name_{ name }
    {}

    void page::name_update(const QString& name)
    {
        name_ = name;

        ndb::query<dbs::core>() << (ndb::set(nxi_model.page.name = name_) << ndb::filter(nxi_model.page.id == id_));

        emit event_update_name(name_);
    }

    void page::load()
    {
        emit event_load();
    }


    nxi::page_id page::id() const
    {
        return id_;
    }

    const QString& page::name() const
    {
        return name_;
    }
} // nxi