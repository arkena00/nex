#ifndef RESOURCE_TYPE_H_NXS
#define RESOURCE_TYPE_H_NXS

#include <nxs/database.hpp>

namespace nxs
{
    class type : public db::entity<nxs::type>
    {
    private:
        std::string _name;
        std::string _image;
        std::string _description;
        std::string _author;

        void hydrate(const db::line&);

    public:
        static const db::tables::type& db_ref;

        type(const db::line&);
        type(int id);

        const std::string& name() const;
        const std::string& image() const;
        const std::string& description() const;
        const std::string& author() const;

        static int add(const std::string& name,
                       const std::string& image = "",
                       const std::string& description = "",
                       const std::string& author = "anonymous");
    };
} // nxs

#endif // RESOURCE_TYPE_H_NXS
