#ifndef UTILITY_FILE_H_NXS
#define UTILITY_FILE_H_NXS

#include <boost/filesystem.hpp>
#include <string>

namespace nxs
{
    class file
    {
    public:
        static std::string rename(const std::string& path, const std::string& name);
        static bool exist(const std::string& path);
    };
}

#endif // UTILITY_FILE_H_NXS
