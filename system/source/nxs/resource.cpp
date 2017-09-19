#include <nxs/resource.hpp>
#include <nxs/error.hpp>

namespace nxs
{
    const db::tables::resource& resource::db_ref = db::nex.resource;

    resource::resource(int id) : db::entity<resource>(id)
    {
        try {
        hydrate(Entity::data());
        } catch (const std::exception&) { nxs_error << "can't load resource :" << id << log::database; }
    }
    resource::resource(const db::line& data) : db::entity<resource>(data)
    {
        hydrate(data);
    }

    void resource::hydrate(const db::line& data)
    {
        const auto& r = db::nex.resource;
        const auto& t = db::nex.type;
        const auto& rc = db::nex.resource_connexion;


        is_node_ = false;
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

        // check if resource has node
        db::result res_node = db::query() << (rc.source_id) << (rc.source_id == _id);
        if (res_node.size() > 0) is_node_ = true;

        //resource.type("movie").property("name")
        //resource.data("movie", "name")
    }

    const std::string& resource::name() const
    {
        return _name;
    }

    bool resource::is_node() const
    {
        return is_node_;
    }

    const resource::Type_List& resource::type_get() const
    {
        return _type;
    }

////////////////////////////////////////////////////////////////////////////////
////////////////////////             STATIC             ////////////////////////
////////////////////////////////////////////////////////////////////////////////
    int resource::add(const std::string& name, int source_id)
    {
        auto& rc = db::nex.resource_connexion;
        db::result res = db::query() + (db::nex.resource.name = name);
        int new_id = res.add_id();

        // add resource connexion
        db::result res_rc = db::query() + (
        rc.source_id = source_id,
        rc.target_id = new_id,
        rc.target_address = "localhost",
        rc.connexion_id = 0);

        return new_id;
    }

    std::vector<resource> resource::get(int source_id)
    {
        auto& r = db::nex.resource;
        auto& rc = db::nex.resource_connexion;
        std::vector<resource> vec;
        db::result res = db::query() << (r.all()) << (rc.target_id == r.id) << (rc.source_id == source_id);
        for(auto& item : res) vec.push_back(resource(item));
        return vec;
    }

    db::result resource::del(int id)
    {
        const auto& r = db::nex.resource;
        const auto& rc = db::nex.resource_connexion;
        // check if resource has target connections
        db::result res = db::query() << rc.source_id << (rc.source_id == id);
        if (res.has_result()) nxs_error << "can't delete a resource with target connections" << log::database;

        // delete connections
        db::result res_del  = db::query() - (rc.target_id == id);
        return db::query() - (r.id == id);
    }

    db::result resource::type_add(int id, int type_id)
    {
        return db::query() + (db::nex.resource.type.id = type_id, db::nex.resource.id = id);
    }
} // nxs
