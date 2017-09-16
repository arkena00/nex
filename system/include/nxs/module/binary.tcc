#include <nxs/log.hpp>

namespace nxs
{
    template<class T>
    binary_module<T>::binary_module(int id) : base_module<T>(id),
        m_handle(nullptr),
        m_main_ptr(nullptr),
        m_load_ptr(nullptr)
    {}

    template<class T>
    bool binary_module<T>::load()
    {
        using Base_module = base_module<T>;

        if (!Base_module::exist() || Base_module::is_loaded()) return false;

        try {
        // load module
        Base_module ::m_is_loaded = true;
        m_handle = NXS_OS_MODULE_LOAD(Base_module::path().c_str());
        if (m_handle == 0)
        {
            nxs_log << "file not found : " << Base_module::path();
            Base_module ::m_is_loaded = false;
            return false;
        }

        // get main pointer
        m_main_ptr = reinterpret_cast<Module_main_ptr>(NXS_OS_MODULE_FUNCTION(m_handle, "nex_main"));
        if (!m_main_ptr) { nxs_log << "function nex_main missing"; return 0; }
        // get load pointer and call
        m_load_ptr = reinterpret_cast<Module_load_ptr>(NXS_OS_MODULE_FUNCTION(m_handle, "nex_load"));
        if (m_load_ptr)
        {
            m_load_ptr();
            db::engine::set("nxs"); // set nxs db if module changed it
        }
        } catch (const std::exception& e)
        {
            nxs_log << "can t load module :" << e.what();
            Base_module ::m_is_loaded = false;
            return false;
        }

        return true;
    }

    template<class T>
    void binary_module<T>::unload()
    {
        if (!base_module<T>::is_loaded()) return;
        NXS_OS_MODULE_UNLOAD(m_handle);
        base_module<T>::unload();
    }

    template<class T>
    int binary_module<T>::process(nxs::nex& nex)
    {
        try {
        m_main_ptr(nex);
        } catch (const std::exception& e) { nxs_error << "module error" << e.what() << log::system; }
        return 0;
    }

} // nxs
