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


    void user::login(const std::string& name, const std::string& pass)
    {

    }
} // nxs
