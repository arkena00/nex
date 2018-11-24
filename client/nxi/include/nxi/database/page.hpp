#ifndef DATABASE_PAGE_H_NXI
#define DATABASE_PAGE_H_NXI

#include <ndb/preprocessor.hpp>

ndb_table(
    page
    , ndb_field_id
    , ndb_field(name, QString)
    , ndb_field(type, nxi::page_type)
)

ndb_table(
    page_connection
    , ndb_field(source_id, nxi::page_id)
    , ndb_field(target_id, nxi::page_id)
)

#endif // DATABASE_PAGE_H_NXI