//! \file nxs.h
//! \author ads
//! \details This file is used by modules / interfaces to import functions from nxs
//! \date 10/08/2014

#ifndef NXS_SHARED_H_NXS
#define NXS_SHARED_H_NXS

#include <nxs/os/share.hpp>

// import
// previously export, redefine to import
#undef NXS_SHARED
#define NXS_SHARED NXS_IMPORT
#define NXS_IMPORTED

#include <nxs/core/nxs.hpp>

#endif // NXS_SHARED_H_NXS
