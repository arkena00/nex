#ifndef NXI_ERROR_H_NXI
#define NXI_ERROR_H_NXI

#include <nxs/error.hpp>

#define nxi_error throw nxs::error(NXS_LINE, NXS_FUNC_NAME, "nxi")

#define nxi_assert(C) Q_ASSERT(C)


using nxs::log;

#endif // ERROR_H_NXI
