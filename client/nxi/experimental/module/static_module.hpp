#ifndef NXI_STATIC_MODULE_H_NXI
#define NXI_STATIC_MODULE_H_NXI

#include "experimental/module/test/test.hpp"

namespace nxi
{
	class core;

    class static_module_container
    {
    public:
		explicit static_module_container(nxi::core& nxi_core) :
			nxi_core_{ nxi_core }
			, m_test{ nxi_core }
		{}

        void load()
		{
			m_test.load();
		}

    private:
		nxi::core& nxi_core_;

        nxi::modules::test m_test;
    };
} // nxi

#endif // NXI_STATIC_MODULE_H_NXI