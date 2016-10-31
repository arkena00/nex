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
        std::chrono::time_point<std::chrono::system_clock> _date_creation;

    public:
        resource(int id);

        int id() const;
        const std::string& name() const;

        static std::vector<resource> list();
        //static db::result add(const std::string& name);
        static db::result get();

        static db::result type_add(int id, int type_id);
    };
} // nxs

#endif // RESOURCE_H_NXS
