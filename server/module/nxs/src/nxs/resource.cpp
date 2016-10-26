#include <nxs/resource.hpp>

namespace nxs
{
    const auto& r = db::nex.resource;

    int resource::id() const { return _id; }
    const std::string& resource::name() const { return _name; }

    db::result resource::add(const std::string& name)
    {
        return db::query() + (r.name = name, r.owner.id = 0);
    }

    db::result resource::get()
    {
        return db::query() << (r.id, r.name);
    }
} // nxs
