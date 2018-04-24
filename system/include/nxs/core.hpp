#ifndef CORE_H_NXS
#define CORE_H_NXS

#include <string>
#include <ndb/initializer.hpp>
#include <ndb/engine/sqlite/sqlite.hpp>

namespace nxs
{
    class core
    {
    public:
        core();

        std::string version() const;

    private:
        ndb::initializer<ndb::sqlite> ndb_;
    };
} // nxs

#endif // CORE_H_NXS
