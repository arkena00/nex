#include <fstream>
#include <nxs/database.hpp>

namespace nxs
{
    template<class T>
    text_module<T>::text_module(int id) : base_module<T>(id) {}

    template<class T>
    bool text_module<T>::load()
    {
        using Base_module = base_module<T>;

        if (!Base_module::exist() || Base_module::is_loaded()) return false;

        // load module
        std::ifstream file(Base_module::path(), std::ios::binary | std::ios::in);
        if (file.is_open())
        {
            char buffer[512] = {0};
            while (!file.eof())
            {
                file.read(buffer, 512);
                m_text += std::string(buffer, static_cast<size_t>(file.gcount()));
            }
            file.close();
        }
        else { nxs_log << "can't open file : " << Base_module::path(); return false; }

        Base_module::m_is_loaded = true;
        return true;
    }

    template<class T>
    int text_module<T>::process(nxs::nex& nex)
    {
        try {
        nex.output().add(std::move(m_text));
        } catch (const std::exception& e) { nxs_error << "module error" << e.what(); }
        return 0;
    }

} // nxs
