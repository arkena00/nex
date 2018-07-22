#ifndef DATABASE_H_NXI
#define DATABASE_H_NXI

#include <ndb/engine/sqlite/sqlite.hpp>

#include <ndb/preprocessor.hpp>

#include <ndb/query.hpp>
#include <ndb/expression.hpp>


#include <nxi/database/window.hpp>


ndb_model(nxi_model,
          window
)

ndb_project(nxi_project,
            ndb_database(db_ui, nxi_model, ndb::sqlite)
)

namespace dbs
{
    using ui = ndb::databases::nxi_project::db_ui_;
} // nxi

using ndb::models::nxi_model;

#endif // DATABASE_H_NXI