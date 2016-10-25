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
            user(*this)
        {}
    } // models

    namespace tables
    {
        user::user(ndb::model<>& m, ndb::table_option<> option) : table(m, "user", option),
            id(*this, "id", field_option<>::id()),
            name(*this, "name", field_option<>::not_null | field_option<>::unique),
            pass(*this, "pass")
        {}

        type::type(ndb::model<>& m, ndb::table_option<> option) : table(m, "type", option),
            id(*this, "id", field_option<>::id()),
            name(*this, "name"),
            image(*this, "image"),
            description(*this, "description"),
            author(*this, "author")
        {
            table_option<>::unique(*this, {name, author});
        }

        resource::resource(ndb::model<>& m) : table(m, "resource"),
            id(*this, "id", field_option<>::id()),
            name(*this),
            owner(*this),
            date_creation(*this),
            type(*this)
        {}
    } // tables

    const models::nex nex;
} // ndb
