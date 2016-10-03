#ifndef CORE_NXS_H_NXS
#define CORE_NXS_H_NXS

// core include
#include <nxs/os/share.hpp>
#include <nxs/core/error.hpp>
#include <string>

namespace nxs
{
    class nex;

	std::string NXS_SHARED version();
    void NXS_SHARED load();

    void execute(nxs::nex& nex);
} // nxs

#endif // CORE_NXS_H_NXS
