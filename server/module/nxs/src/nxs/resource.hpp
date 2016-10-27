#ifndef RESOURCE_H_NXS
#define RESOURCE_H_NXS

#include <nxs/database.hpp>
#include <nxs/resource/type.hpp>

namespace nxs
{
    class resource
    {
    private:
        int _id;
        std::string _name;
        nxs::type _type;

    public:
        resource() = delete;

        int id() const;
        const std::string& name() const;

        static db::result add(const std::string& name);
        static db::result get();

    static db::result type_add(int id, int type_id)
    {
        db::query q;
        q + (db::nex.resource.type.id = type_id, db::nex.resource.id = id);
        std::cout << q.native();
        return q.exec();
    }

        static std::vector<resource> list()
        {
            std::vector<resource> l;
            db::query q;
            q << (db::nex.resource.name, db::nex.resource.type.name);
            db::result r = q.exec();

            return l;
        }
    };
} // nxs

#endif // RESOURCE_H_NXS
