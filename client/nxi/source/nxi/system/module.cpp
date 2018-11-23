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
        for (auto& module : ndb::oget<dbs::core>(nxi_model.module))
        {
            std::unique_ptr<nxi::module> module_ptr;

            switch(module.type)
            {
                case nxi::module_type::dynamic:
                    module_ptr = std::make_unique<nxi::dynamic_module>(nxi_core_, module.name);
                    break;

                case nxi::module_type::web:
                    module_ptr = std::make_unique<nxi::web_module>(nxi_core_, module.name);
                    break;

                default:
                    nxi_error << "module load type";
            }

            // if (state == enable)
            module_ptr->load();

            modules_.push_back(std::move(module_ptr));
        }
        //emit event_load(module_name);
    }

} // nxi