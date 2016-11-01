#include <nxs/database.hpp>

namespace db
{
    using ndb::field_option;
    using ndb::table_option;

    namespace models
    {
        nex::nex() :
            resource(*this),
            type(*this),
            property(*this),
            user(*this)
        {}
    } // models

    namespace tables
    {
        user::user(ndb::model<>& m, ndb::table_option<> option) : table(m, "user", option),
            id(*this, field_option<>::id()),
            name(*this, field_option<>::not_null | field_option<>::unique),
            pass(*this)
        {}

        type::type(ndb::model<>& m, ndb::table_option<> option) : table(m, "type", option),
            id(*this, field_option<>::id()),
            name(*this),
            image(*this),
            description(*this),
            author(*this),
            property(*this)
        {
            table_option<>::unique(*this, {name, author});
        }

        property::property(ndb::model<>& m, ndb::table_option<> option) : table(m, "property", option),
            id(*this, field_option<>::id()),
            name(*this),
            type(*this),
            type_data(*this)
        {
            table_option<>::unique(*this, {name, type});
        }

        resource::resource(ndb::model<>& m) : table(m, "resource"),
            id(*this, field_option<>::id()),
            name(*this),
            owner(*this),
            date_creation(*this),
            type(*this),
            property(*this)
        {}
    } // tables

    const models::nex nex;
} // ndb
