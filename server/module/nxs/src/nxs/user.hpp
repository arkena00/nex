#ifndef USER_H_NXS
#define USER_H_NXS

#include <nxs/database.hpp>

namespace nxs
{
    class user
    {
    private:

    public:
        static db::result add(const std::string& name, const std::string& pass)
        {
            return db::query() + (db::nex.user.name = name, db::nex.user.pass = pass);
        }
    };
} // nxs

#endif // USER_H_NXS
