#ifndef NXI_DATABASE_H_NXI
#define NXI_DATABASE_H_NXI

#include <ndb/engine/sqlite/sqlite.hpp>

#include <ndb/preprocessor.hpp>
#include <ndb/field.hpp>
#include <ndb/table.hpp>
#include <ndb/database.hpp>

#include <ndb/query.hpp>
#include <ndb/function.hpp>

ndb_table(window,
          ndb_field_id,
          ndb_field(x, int),
          ndb_field(y, int)
)

ndb_table(shortcut,
          ndb_field_id,
          ndb_field(parent_id, int),
          ndb_field(combo_keys, std::vector<char>, ndb::size<16>),
          ndb_field(sequence_keys, std::vector<char>, ndb::size<16>),
          ndb_field(name, std::string, ndb::size<255>),
          ndb_field(action, std::string, ndb::size<255>)
)

ndb_model(nxi_model,
          window,
          shortcut
)

ndb_project(nxi_project,
            ndb_database(nxi_db, nxi_model, ndb::sqlite)
)

namespace nxi
{
    using db_main = ndb::databases::nxi_project::nxi_db_;
} // nxi

using ndb::models::nxi_model;

namespace db
{
    using query = ndb::query<nxi::db_main>;
} // db

#endif // NXI_DATABASE_H_NXI