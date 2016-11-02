#include <nxs/resource.hpp>
#include <nxs/error.hpp>

namespace nxs
{
    const auto& r = db::nex.resource;
    const auto& t = db::nex.type;

    resource::resource(const db::line& data) : db::entity<nxs::resource>(data)
    {
        hydrate(data);
    }
    resource::resource(int id) : db::entity<nxs::resource>(id)
    {
        hydrate(db::entity<nxs::resource>::data());
    }

    void resource::hydrate(const db::line& data)
    {
        _name = data[r.name];
        _date_creation = data[r.date_creation];

        db::query q;
        q << (r.type.id, t.name) << (t.id == r.type.id) << (r.id == id());
        std::cout << q.native();

        //nxs::type type = nxs::type(id);
        //_type.insert(std::make_pair(type.name(), type));
    }

    int resource::id() const { return _id; }
    const std::string& resource::name() const { return _name; }

    //const nxs::user& resource::owner() const { return _owner; }


    std::vector<resource> resource::get()
    {
        std::vector<resource> vec;
        const auto& r = db::nex.resource;
        db::result res = db::query() << (r.id, r.name, r.date_creation);
        for(auto& item : res)
        {
            //vec.push_back(type(item));
        }
        return vec;
    }

    /*
    db::result resource::add(const std::string& name)
    {
        return db::query() + (r.name = name, r.owner.id = 0);
    }*/

    db::result resource::type_add(int id, int type_id)
    {
        return db::query() + (db::nex.resource.type.id = type_id, db::nex.resource.id = id);
    }
} // nxs
