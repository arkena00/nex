#include <nxi/system/module.hpp>

#include <nxi/database/module.hpp>
#include <nxi/core.hpp>
#include <nxi/database.hpp>
#include <nxi/log.hpp>

// include modules
#include "experimental/module/static_module.hpp"

namespace nxi
{
    module_system::module_system(nxi::core& nxi_core) :
		nxi_core_{ nxi_core }
		, m_static_modules{ nxi_core_ }
	{}

    void module_system::load()
    {
        nxi_log << "load module_system";

        // load static modules
        m_static_modules.load();

        auto res = ndb::query<dbs::core>() << (
        ndb::get(nxi_model.module.id, nxi_model.module.name, nxi_model.module.type)
        << ndb::source(nxi_model.module));
        for (auto& line : res)
        {
            nxi::module m;
            m.id = line[nxi_model.module.id];
            m.name = line[nxi_model.module.name];
            m_modules.push_back(m);
        }
    }

} // nxi