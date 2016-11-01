#ifndef DATABASE_H_NXS
#define DATABASE_H_NXS

#include <ndb/error.hpp>
#include <ndb/engine.hpp>
#include <ndb/model.hpp>
#include <ndb/table.hpp>
#include <ndb/field.hpp>
#include <ndb/query.hpp>
#include <ndb/result.hpp>
#include <ndb/entity.hpp>

// alias
namespace db
{
    using query = ndb::query<>;
    using result = ndb::result<>;
    using line = ndb::line<>;
    template<class T>
    using entity = ndb::entity<T>;

} // db

namespace db
{
    using ndb::field;

    namespace tables
    {
        struct user : public ndb::table<>
        {
            field<int> id;
            field<std::string, 255> name;
            field<std::string, 512> pass;

            user(ndb::model<>& m, ndb::table_option<> option = {});
        };

        struct property : public ndb::table<>
        {
            field<int> id;
            field<std::string, 64> name;
            field<int> type;
            field<std::string, 255> type_data;

            property(ndb::model<>& m, ndb::table_option<> option = {});
        };

        struct interface : public ndb::table<>
        {
            field<int> id;
            field<std::string, 255> name;
            field<std::string, 255> image;
            field<std::string> description;
            field<std::string, 255> author;

            interface(ndb::model<>& m, ndb::table_option<> option = {});
        };

        struct type : public ndb::table<>
        {
            field<int> id;
            field<std::string, 255> name;
            field<std::string, 255> image;
            field<std::string> description;
            field<std::string, 255> author;
            field<tables::property> property;

            type(ndb::model<>& m, ndb::table_option<> option = {});
        };

        struct resource : public ndb::table<>
        {
            field<int> id;
            field<std::string, 255> name;
            field<tables::user, 1> owner;
            field<tables::user, 1> admin;
            field<std::chrono::time_point<std::chrono::system_clock>> date_creation;
            // field<std::chrono::time_point<std::chrono::system_clock>> date_edition;
            // field<std::chrono::time_point<std::chrono::system_clock>> date_expiration;
            // field<std::chrono::time_point<std::chrono::system_clock>> date_delete;
            // field<int> fiability;
            // field<int> fiability_vote;
            // field<int> quality;
            // field<int> quality_vote;
            // field<int> popularity;
            // field<int> network;
            // field<std::string, 255> author;
            // field<std::string, 255> source;
            // field<std::string, 2> language;

            field<tables::type> type;
            field<tables::property> property;

            resource(ndb::model<>& m);
        };
    } // tables

    namespace models
    {
        struct nex : ndb::model<>
        {
            tables::resource resource;
            tables::type type;
            tables::property property;
            tables::user user;

            nex();
        };
    } // models

    extern const models::nex nex;
} // db

#endif // DATABASE_H_NXS
