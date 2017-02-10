namespace nxs
{
    template<class T>
    binary_module<T>::binary_module(int id) : base_module<T>(id),
        _handle(nullptr),
        _main_ptr(nullptr),
        _load_ptr(nullptr)
    {}

    template<class T>
    bool binary_module<T>::load()
    {
        using A_Module = base_module<T>;

        if (!db::entity<T>::exist() || A_Module::is_loaded()) return false;

        try {
        // load module
        _handle = NXS_OS_MODULE_LOAD(A_Module::path().c_str());
        if (_handle == 0) { nxs_log("file not found : " + A_Module::path()); return false; }

        // get main pointer
        _main_ptr = reinterpret_cast<Module_main_ptr>(NXS_OS_MODULE_FUNCTION(_handle, "nex_main"));
        if (!_main_ptr) { nxs_log("function nex_main missing"); return 0; }
        // get load pointer and call
        _load_ptr = reinterpret_cast<Module_load_ptr>(NXS_OS_MODULE_FUNCTION(_handle, "nex_load"));
        if (_load_ptr)
        {
            _load_ptr();
            db::engine::set("nxs"); // set nxs db if module changed it
        }
        } catch (const std::exception& e) { nxs_log(std::string("can t load module : ") + e.what()); return false; }

        A_Module::_is_loaded = true;
        return true;
    }

    template<class T>
    void binary_module<T>::unload()
    {
        if (!base_module<T>::is_loaded()) return;
        NXS_OS_MODULE_UNLOAD(_handle);
        base_module<T>::unload();
    }

    template<class T>
    int binary_module<T>::process(nxs::nex& nex)
    {
        try {
        _main_ptr(nex);
        } catch (const std::exception& e) { nxs_error(errc::module, e.what()); }
        return 0;
    }

} // nxs
