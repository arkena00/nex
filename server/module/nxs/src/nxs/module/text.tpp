#include <fstream>
#include <nxs/database.hpp>

namespace nxs
{
    template<class T>
    text_module<T>::text_module(int id) : base_module<T>(id) {}

    template<class T>
    bool text_module<T>::load()
    {
        using A_Module = base_module<T>;

        if (!db::entity<T>::exist() || A_Module::is_loaded()) return false;

        // load module
        std::ifstream file(A_Module::path(), std::ios::binary | std::ios::in);
        if (file.is_open())
        {
            char buffer[512] = {0};
            while (!file.eof())
            {
                file.read(buffer, 512);
                _text += std::string(buffer, file.gcount());
            }
            file.close();
        }
        else { nxs_log << "can't open file : " << A_Module::path() << log::system; return false; }

        A_Module::_is_loaded = true;
        return true;
    }

    template<class T>
    int text_module<T>::process(nxs::nex& nex)
    {
        try {
        nex.output().add(_text);
        } catch (const std::exception& e) { nxs_error(errc::module, e.what()); }
        return 0;
    }

} // nxs
