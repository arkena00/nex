#ifndef ERROR_H_NXI
#define ERROR_H_NXI

#include <nxs/error.hpp>

#define nxi_error throw nxs::error(NXS_LINE, NXS_FUNC_NAME, "nxi")

namespace ui
{
    using nxs::log;
} // nxi

#endif // ERROR_H_NXI
