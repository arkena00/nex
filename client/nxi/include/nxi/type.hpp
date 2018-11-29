#ifndef NXI_TYPE_H_NXI
#define NXI_TYPE_H_NXI

#include <nxi/page/id.hpp>

namespace nxi
{
    enum class page_type { node, web, explorer, custom };
    enum class module_type { compiled, dynamic, web };

} // nxi

#endif // NXI_TYPE_H_NXI