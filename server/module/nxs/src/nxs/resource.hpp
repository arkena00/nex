#ifndef RESOURCE_H_NXS
#define RESOURCE_H_NXS

#include <nxs/database.hpp>
#include <nxs/resource/type.hpp>

namespace nxs
{
    class resource : public db::entity<nxs::resource>
    {
        using Entity = db::entity<nxs::resource>;
        using Type_List = std::vector<nxs::type>;
        using Type_List_Str = std::map<std::string, int>;
    private:
        // nxs::user& _user;
        std::string _name;
        std::chrono::time_point<std::chrono::system_clock> _date_creation;
        Type_List _type;
        Type_List_Str _type_str;

        void hydrate(const db::line&);

    public:
        static const db::tables::resource& db_ref;
        resource(int id);
        resource(const db::line&);

        int id() const;
        const std::string& name() const;

        // std::vector<resource> list() const;
        const Type_List& type_get() const;
        static db::result type_add(int id, int type_id);
    };
} // nxs

#endif // RESOURCE_H_NXS
