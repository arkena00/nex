#include <nxi/system/module.hpp>

#include <nxi/core.hpp>
#include <nxi/database/module.hpp>
#include <nxi/log.hpp>
#include <nxi/module/web.hpp>
#include <nxi/module/binary.hpp>
#include <include/nxi/system/module.hpp>


// include modules
#include "experimental/module/static_module.hpp"

namespace nxi
{
    module_system::module_system(nxi::core& nxi_core) :
		nxi_core_{ nxi_core }
		, static_modules_{ nxi_core_ }
	{}

    const std::vector<std::unique_ptr<nxi::module>>& module_system::get() const
    {
        return modules_;
    }

    void module_system::load()
    {
        nxi_log << "load module_system";

        // load static modules
        static_modules_.load();

        // load db modules
        auto res = ndb::oquery<dbs::core>() << (
        ndb::get(nxi_model.module.id, nxi_model.module.name, nxi_model.module.type)
        << ndb::source(nxi_model.module));
        for (const auto& module_data : res)
        {
            std::unique_ptr<nxi::module> module;
            const QString& module_name = module_data[nxi_model.module.name];

            if (module_data[nxi_model.module.type] == (int)nxi::module_type::dynamic) module = std::make_unique<nxi::dynamic_module>(nxi_core_, module_name);
            else if (module_data[nxi_model.module.type] == (int)nxi::module_type::web) module = std::make_unique<nxi::web_module>(nxi_core_, module_name);
            else nxi_error << "module load type";

            // if (state == enable)
            module->load();

            modules_.push_back(std::move(module));
        }
        //emit event_load(module_name);
    }

} // nxi