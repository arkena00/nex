#ifndef RESOURCE_H_NXS
#define RESOURCE_H_NXS

#include <nxs/database.hpp>

namespace nxs
{
    class resource
    {
    private:
        int _id;
        std::string _name;

    public:
        resource() = delete;

        int id() const;
        const std::string& name() const;

        static db::result add(const std::string& name);
        static db::result get();
    };
} // nxs

#endif // RESOURCE_H_NXS
