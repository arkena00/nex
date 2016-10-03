#ifndef MODEL_STATIC_H_NDB
#define MODEL_STATIC_H_NDB

#include <ndb/field.hpp>
#include <ndb/table.hpp>
#include <ndb/model.hpp>
#include <chrono>

namespace ndb
{
    namespace tables
    {
        struct user : public table<>
        {
            field<int> id;
            field<std::string, 255> name;
            field<std::string, 512> pass;

            user(ndb::model<>& m, ndb::table_option<> option = {});
        };

        struct type : public table<>
        {
            field<int> id;
            field<std::string, 255> name;
            field<std::string, 255> image;
            field<std::string> description;
            field<std::string, 255> author;

            type(ndb::model<>& m, ndb::table_option<> option = {});
        };

        struct interface : public table<>
        {
            field<int> id;
            field<std::string, 255> name;
            field<std::string, 255> image;
            field<std::string> description;
            field<std::string, 255> author;

            interface(ndb::model<>& m, ndb::table_option<> option = {});
        };

        struct resource : public table<>
        {
            field<int> id;
            field<std::string, 255> name;
            field<tables::user, 1> owner;
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

            resource(ndb::model<>& m);
        };
    } // tables

    namespace models
    {
        struct nex : ndb::model<>
        {
            tables::resource resource;
            tables::type type;
            tables::user user;

            nex();
        };
    } // models

    extern const models::nex nex;
} // ndb

#endif // MODEL_STATIC_H_NDB
