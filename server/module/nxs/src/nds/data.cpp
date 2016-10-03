#include <nds/data.hpp>
#include <string>

namespace nds
{
    template<>
    data::data(const std::string& v) { _data.insert(_data.begin(), v.begin(), v.end()); }

    template<>
    std::string data::get() const { return std::string(_data.data(), _data.size()); }
} // nds

