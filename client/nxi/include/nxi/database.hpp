#ifndef DATABASE_H_NXI
#define DATABASE_H_NXI

#include <ndb/engine/sqlite/sqlite.hpp>

#include <ndb/preprocessor.hpp>

#include <ndb/query.hpp>
#include <ndb/expression.hpp>


#include <nxi/database/window.hpp>
#include <nxi/database/module.hpp>


ndb_model(
    nxi_model
    , window
    , module
)

ndb_project(nxi_project,
            ndb_database(db_core, nxi_model, ndb::sqlite)
)

namespace dbs
{
    using core = ndb::databases::nxi_project::db_core_;
} // nxi

using ndb::models::nxi_model;

#endif // DATABASE_H_NXI