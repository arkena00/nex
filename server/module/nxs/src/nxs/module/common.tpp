//! \file common_module.tcc
//! \brief module class
//! \author ads
//! \date 2015-12-06

namespace nxs
{
    // protected:
    template<class T>
    common_module<T>::common_module(int id) : base_module<T>(id) {}

    // initialize all modules
    template<class T>
    void common_module<T>::init()
    {
        const auto& m = T::db_ref;
        log::list(log::system, "loading " + std::string(T::name_));
        // load path ./module/
        db::result res = db::query() << m.all();
        for(size_t i = 0; i != res.size(); i++)
        {
            int id = res[i][m.id];
            std::string ext = res[i][m.ext];
            nxs_log("\n" + res[i][m.name] + " ");

            bool load_ok = load(id, ext);

            if (load_ok) nxs_log(" OK");
            else nxs_log(" ERROR");
        }
        log::list();
    }

    template<class T>
    bool common_module<T>::load(int id, const std::string& ext)
    {
        if (ext == "dl") return load<binary_module<T>>(id);
        else if (ext == "html") return load<text_module<T>>(id);
        else nxs_log("unsupported ext : " + ext);
        return false;
    }

    template<class T>
    template<class M_Type>
    bool common_module<T>::load(int id)
    {
        if (base_module<T>::is_loaded(id)) { nxs_warning("module already loaded " + std::to_string(id)); return false; }
        // create module
        auto m = std::make_unique<M_Type>(id);
        if (!m->load()) return false;
        // module load ok, store it
        base_module<T>::store(std::move(m));

        return true;
    }

} // nxs

