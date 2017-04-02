//! \file module.hpp
//! \brief file included by modules or interfaces
//! \author ads
//! \date 2015-12-26

#ifndef MODULE_SHARE_H_NXS
#define MODULE_SHARE_H_NXS

#include <nxs/share.hpp>

namespace nxs { class nex; }

extern "C"
{
    // prototype for nex module / interface
    int NXS_EXPORT nex_load();
    int NXS_EXPORT nex_main(nxs::nex&);
}

#endif // MODULE_SHARE_H_NXS
