#include <nxs/resource.hpp>
#include <nxs/error.hpp>

namespace nxs
{
    resource::resource(int id) : db::entity<resource>(id)
    {
        try {
        hydrate(db::entity<resource>::data());
        } catch (const std::exception& e) { nxs_error(errc::database, "can't load resource : " + std::to_string(id)); }
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

    int resource::id() const { return db::entity<resource>::id(); }
    const std::string& resource::name() const { return _name; }

    const resource::Type_List& resource::type_get() const { return _type; }

    db::result resource::type_add(int id, int type_id)
    {
        return db::query() + (db::nex.resource.type.id = type_id, db::nex.resource.id = id);
    }
} // nxs
