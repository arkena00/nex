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
            module(*this),
            module_data(*this),
            interface(*this),
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

        module::module(ndb::model<>& m, ndb::table_option<> option) : table(m, "module", option),
            id(*this, field_option<>::id()),
            name(*this),
            image(*this),
            description(*this),
            author(*this, "nex"),
            tag(*this),
            ext(*this, "dl")
        {
            table_option<>::unique(*this, {name, author});
        }

        module_data::module_data(ndb::model<>& m, ndb::table_option<> option) : table(m, "module_data", option),
            id(*this, field_option<>::id()),
            key(*this),
            value(*this)
        {
        }

        interface::interface(ndb::model<>& m, ndb::table_option<> option) : table(m, "interface", option),
            id(*this, field_option<>::id()),
            name(*this),
            image(*this),
            description(*this),
            author(*this, "nex"),
            tag(*this),
            ext(*this, "dl")
        {
            table_option<>::unique(*this, {name, author});
        }

        resource::resource(ndb::model<>& m) : table(m, "resource"),
            id(*this, field_option<>::id()),
            name(*this),
            owner(*this),
            admin(*this),
            date_creation(*this),
            type(*this),
            property(*this)
        {}
    } // tables

    NXS_SHARED models::nex nex;
} // db


namespace nxs{namespace database
{
    void init()
    {
        ndb::engine<>::model_add(db::nex);
        ndb::engine<>::connect("nxs");

        const auto& r = db::nex.resource;
        const auto& t = db::nex.type;
        const auto& md = db::nex.module_data;

        // add system data
        if (db::engine::get().is_init())
        {
            // root resource
            db::result res = db::query() + (r.id = 0, r.name = "ROOT");
            // generic type
            res = db::query() + (t.id = 0, t.name = "generic");
            // nxs data
            res = db::query() + (md.id = 0, md.key = "port", md.value = "50");
        }
    }
}} // nxs::database
