#include <nxs/resource.hpp>
#include <nxs/error.hpp>

namespace nxs
{
    const db::tables::resource& resource::db_ref = db::nex.resource;

    resource::resource(int id) : db::entity<resource>(id)
    {
        try {
        hydrate(Entity::data());
        } catch (const std::exception& e) { nxs_error << "can't load resource :" << id << log::database; }
    }
    resource::resource(const db::line& data) : db::entity<resource>(data)
    {
        hydrate(data);
    }

    void resource::hydrate(const db::line& data)
    {
        const auto& r = db::nex.resource;
        const auto& t = db::nex.type;

        _name = data[r.name];
        _date_creation = data[r.date_creation];

        db::result res = db::query() << (r.id, t.id, t.name) << (r.type.id == r.id, t.id == r.type.id) << (r.id == id());

        for (const auto& item : res)
        {
            nxs::type type = nxs::type(item);
            _type.push_back(type);
            // link type string to vector index
            _type_str.insert(std::make_pair(type.name(), _type.size()));
        }

        //resource.type("movie").property("name")
        //resource.data("movie", "name")
    }

    const std::string& resource::name() const
    {
        return _name;
    }

    const resource::Type_List& resource::type_get() const
    {
        return _type;
    }


    std::vector<resource> resource::get(int source_id)
    {
        std::vector<resource> vec;
        db::result res = db::query() << (db::nex.resource.all()) << (db::nex.resource.id = source_id);
        for(auto& item : res) vec.push_back(resource(item));
        return vec;
    }

    db::result resource::type_add(int id, int type_id)
    {
        return db::query() + (db::nex.resource.type.id = type_id, db::nex.resource.id = id);
    }
} // nxs
