#ifndef USER_H_NXS
#define USER_H_NXS

#include <nxs/database.hpp>

namespace nxs
{
    class user
    {
    private:

    public:
        static ndb::result<> add(const std::string& name, const std::string& pass)
        {
            return ndb::query<>() + (ndb::nex.user.name = name, ndb::nex.user.pass = pass);
        }
    };
} // nxs

#endif // USER_H_NXS
