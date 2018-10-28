#ifndef NXI_MODULE_SYSTEM_H_NXI
#define NXI_MODULE_SYSTEM_H_NXI

#include <nxi/module.hpp>

#include <QObject>
#include <experimental/module/static_module.hpp>

namespace nxi
{
	class core;

    class module_system : public QObject
    {
        Q_OBJECT
    public:
		module_system(nxi::core&);
		module_system(const module_system&) = delete;
        void operator=(const module_system&) = delete;

        void load();

    private:
		nxi::core& nxi_core_;
        std::vector<nxi::module> m_modules;

        nxi::static_module_container m_static_modules;
    };
} // nxi

#endif // NXI_MODULE_SYSTEM_H_NXI