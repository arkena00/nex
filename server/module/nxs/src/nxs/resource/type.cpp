#include <nxs/resource/type.hpp>

namespace nxs
{
    type::type(const db::line& data) : db::entity<nxs::type>(data)
    {
        hydrate(data);
    }
    type::type(int id) : db::entity<nxs::type>(id)
    {
        hydrate(db::entity<nxs::type>::data());
    }

    void type::hydrate(const db::line& data)
    {
        const auto& t = db::nex.type;
        _name = data[t.name];
        _image = data.get(t.image, "N/A");
        _description = data.get(t.description, "N/A");
        _author = data.get(t.author, "N/A");
    }

    const std::string& type::name() const { return _name; }
    const std::string& type::image() const { return _image; }
    const std::string& type::description() const { return _description; }
    const std::string& type::author() const { return _author; }

    db::result type::add(const std::string& name, const std::string& image, const std::string& description, const std::string& author)
    {
        const auto& t = db::nex.type;
        return db::query() + (t.name = name, t.image = image, t.description = description, t.author = author);
    }
} // nxs
