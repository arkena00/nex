#include <nxs/utility/file.hpp>
#include <nxs/error.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
namespace nxs
{
    std::string file::rename(const std::string& source_path, const std::string& name)
    {
        if (!nxs::file::exist(source_path)) nxs_error(errc::system, "can't rename file : " + source_path);
        boost::filesystem::path source(source_path);
        boost::filesystem::path target(name);
        std::string path = source.parent_path().generic_string() + "/";
        std::string target_name = target.stem().generic_string();
        std::string target_ext = target.extension().generic_string();

        std::string renamepath = path + target_name + target_ext;
        // rename file
        int i = 1;
        while (nxs::file::exist(renamepath))
        {
            renamepath = path + target_name + "_" + std::to_string(i++) + target_ext;
        }
        boost::filesystem::rename(source_path, renamepath);
        return renamepath;
    }

    bool file::exist(const std::string& p)
    {
        return boost::filesystem::exists(p);
    }

} // nxs
