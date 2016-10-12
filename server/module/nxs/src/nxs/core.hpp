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
    class user;

    class NXS_SHARED nex
    {
    public:
        virtual user& user() = 0;
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
