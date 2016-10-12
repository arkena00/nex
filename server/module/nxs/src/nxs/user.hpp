#ifndef USER_H_NXS
#define USER_H_NXS

#include <nxs/database.hpp>

namespace nxs
{
    class user
    {
    private:
        int _id;
        std::string _name;

    public:

        int id() const;
        const std::string name() const;
        bool login(const std::string& name, const std::string& pass);

        static db::result add(const std::string& name, const std::string& pass);
    };
} // nxs

#endif // USER_H_NXS
