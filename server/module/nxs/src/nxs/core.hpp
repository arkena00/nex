#ifndef CORE_NXS_H_NXS
#define CORE_NXS_H_NXS

// core include
#include <nxs/os/share.hpp>
#include <nxs/error.hpp>
#include <string>

// nex interface
namespace nxs
{
    class request;

    class NXS_SHARED nex
    {
    public:
        //virtual nxs::i_cnx& cnx() = 0;
        //virtual nxs::c_user& user() = 0;

        // protocol
        virtual request& input() = 0;
        virtual request& output() = 0;
    };
} // nxs

namespace nxs
{
	std::string NXS_SHARED version();
    void NXS_SHARED load();

    void execute(nxs::nex& nex);
} // nxs

#endif // CORE_NXS_H_NXS
