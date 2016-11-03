#ifndef RESOURCE_H_NXS
#define RESOURCE_H_NXS

#include <nxs/database.hpp>
#include <nxs/resource/type.hpp>

namespace nxs
{
    class resource : public db::entity<nxs::resource>
    {
        using Type_List = std::map<std::string, nxs::type>;
    private:
        std::string _name;
        std::chrono::time_point<std::chrono::system_clock> _date_creation;
        Type_List _type;

        void hydrate(const db::line&);

    public:
        constexpr static const auto& db_ref = db::nex.resource;
        resource(const db::line&);
        resource(int id);

        int id() const;
        const std::string& name() const;

        const Type_List& type_get() const;

        static db::result type_add(int id, int type_id);
    };
} // nxs

#endif // RESOURCE_H_NXS
