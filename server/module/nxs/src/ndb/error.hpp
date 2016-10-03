#ifndef ERROR_H_NDB
#define ERROR_H_NDB

#include <stdexcept>

#define ndb_error(message) throw std::logic_error(message);

#endif // ERROR_H_NDB

