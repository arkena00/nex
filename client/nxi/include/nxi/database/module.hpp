#ifndef DATABASE_MODULE_H_NXI
#define DATABASE_MODULE_H_NXI

#include <ndb/preprocessor.hpp>

ndb_table(
    module
    , ndb_field_id
    , ndb_field(name, QString)
    , ndb_field(type, nxi::module_type)
)

#endif // DATABASE_MODULE_H_NXI