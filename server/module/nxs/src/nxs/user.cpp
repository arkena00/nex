#include <nxs/user.hpp>

namespace nxs
{
    user::user() :
        _id(0),
        _name("anonymous"),
        _logged(false)
    {}

    int user::id() const { return _id; }
    const std::string& user::name() const { return _name; }
    bool user::is_logged() const { return _logged; }

    db::result user::add(const std::string& name, const std::string& pass)
    {
        return db::query() + (db::nex.user.name = name, db::nex.user.pass = pass);
    }

    db::result user::get()
    {
        const auto& u = db::nex.user;
        return db::query() << (u.id, u.name);
    }

    void user::login(const std::string& name, const std::string& pass)
    {
        db::result r = db::query() << (db::nex.user.id, db::nex.user.name) << (db::nex.user.name == name && db::nex.user.pass == pass);
        if (r.size() == 1)
        {
            _id = r[0][db::nex.user.id];
            _name = r[0][db::nex.user.name];
            _logged = true;
        }
    }
} // nxs
