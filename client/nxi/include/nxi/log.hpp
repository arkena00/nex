#ifndef NXI_LOG_H_NXI
#define NXI_LOG_H_NXI

#include <nxs/error.hpp>
#include <iostream>

#define nxi_error throw nxs::error(NXS_LINE, NXS_FUNC_NAME, "nxi")

#define nxi_assert(C) Q_ASSERT(C)

#define nxi_log std::cout << "\n[nxi] "

using nxs::log;

#endif // NXI_LOG_H_NXI