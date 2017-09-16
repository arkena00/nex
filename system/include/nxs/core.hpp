#ifndef CORE_NXS_H_NXS
#define CORE_NXS_H_NXS

// core include
#include <nxs/share.hpp>
#include <nxs/nex.hpp>
#include <nxs/error.hpp>
#include <string>

namespace nxs
{
	std::string version();
	void load();

    void execute(nxs::nex& nex);
} // nxs

#endif // CORE_NXS_H_NXS
