#ifndef USER_H_NXS
#define USER_H_NXS

#include <nxs/os/share.hpp>
#include <nxs/database.hpp>

namespace nxs
{
    class user
    {
    private:
        int _id;
        std::string _name;
        bool _logged;

    public:
        user();

        int id() const;
        const std::string& name() const;
        bool is_logged() const;
        void login(const std::string& name, const std::string& pass);

        static db::result add(const std::string& name, const std::string& pass);
        static db::result get();
    };
} // nxs

#endif // USER_H_NXS
