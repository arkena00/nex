#ifndef RESOURCE_H_NXS
#define RESOURCE_H_NXS

#include <nxs/serialize.hpp>
#include <nxs/database.hpp>
#include <nxs/resource/type.hpp>

namespace nxs
{
    class resource : public db::entity<nxs::resource>
    {
        using Entity = db::entity<nxs::resource>;
        using Type_List = std::vector<nxs::type>;
        using Type_List_Str = std::map<std::string, int>;

        nxs_serialize(Entity::_id & _name & is_node_ & _type)

    private:
        // nxs::user& _user;
        std::string _name;
        bool is_node_;
        std::chrono::time_point<std::chrono::system_clock> _date_creation;
        Type_List _type;
        Type_List_Str _type_str;

        void hydrate(const db::line&);

    public:
        static const db::tables::resource& db_ref;

        resource() = default;
        resource(int id);
        resource(const db::line&);

        const std::string& name() const;
        bool is_node() const;
        const Type_List& type_get() const;

        static int add(const std::string& name, int source_id = 0);
        static std::vector<resource> get(int source_id = 0);
        static db::result del(int id);
        static db::result type_add(int id, int type_id);
    };
} // nxs

#endif // RESOURCE_H_NXS
