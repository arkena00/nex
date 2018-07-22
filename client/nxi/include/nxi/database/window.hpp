#ifndef DATABASE_WINDOW_H_NXI
#define DATABASE_WINDOW_H_NXI

#include <ndb/preprocessor.hpp>

ndb_table(
    window
    , ndb_field_id
    , ndb_field(x, int)
    , ndb_field(y, int)
    , ndb_field(w, int)
    , ndb_field(h, int)
)

#endif // DATABASE_WINDOW_H_NXI