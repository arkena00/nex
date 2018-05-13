#ifndef NXI_DATABASE_H_NXI
#define NXI_DATABASE_H_NXI

#include <ndb/preprocessor.hpp>
#include <ndb/field.hpp>
#include <ndb/table.hpp>
#include <ndb/database.hpp>

#include <ndb/query.hpp>

ndb_table(window,
          ndb_field_id,
          ndb_field(x, int),
          ndb_field(y, int)
)

ndb_model(nxi_model, window)

ndb_project(nxi_project,
            ndb_database(nxi_db, nxi_model, ndb::sqlite)
)

namespace nxi
{
    using db_main = ndb::databases::nxi_project::nxi_db_;
} // nxi


namespace db
{
    using query = ndb::query<nxi::db_main>;
} // db

#endif // NXI_DATABASE_H_NXI