#ifndef CORE_NEX_H_NXS
#define CORE_NEX_H_NXS

#include <nxs/os/share.hpp>

namespace nxs
{
    class request;

    class NXS_SHARED nex
    {
    public:
        virtual ~nex();

        //virtual nxs::i_cnx& cnx() = 0;
        //virtual nxs::c_user& user() = 0;

        // protocol
        virtual request& input() = 0;
        virtual request& output() = 0;
    };
} // nxs

#endif // CORE_NEX_H_NXS
