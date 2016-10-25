#include <nxs/resource.hpp>

namespace nxs
{

    int resource::id() const { return _id; }
    const std::string& resource::name() const { return _name; }

    db::result resource::add(const std::string& name)
    {
        const auto& r = db::nex.resource;
        return db::query() + (r.name = name, r.owner.id = 0);
    }

    db::result resource::get()
    {
        const auto& r = db::nex.resource;
        return db::query() << (r.id, r.name);
    }

} // nxs
