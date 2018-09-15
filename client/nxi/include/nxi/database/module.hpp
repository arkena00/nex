#ifndef DATABASE_MODULE_H_NXI
#define DATABASE_MODULE_H_NXI

#include <ndb/preprocessor.hpp>

ndb_table(
    module
    , ndb_field_id
    , ndb_field(name, std::string)
    , ndb_field(type, int)
)

#endif // DATABASE_WINDOW_H_NXI