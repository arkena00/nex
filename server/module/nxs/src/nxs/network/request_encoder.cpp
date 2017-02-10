#include <nxs/network/request.hpp>
#include <nds/encoder.hpp>
#include <nds/data.hpp>
#include <nxs/network/header.hpp>

using namespace std;

namespace nds
{
    template<> std::string encoder::encode<std::string, nxs::header>(const std::vector<size_t>& value_list)
    {
        std::string result = "";
        for (auto it : value_list)
        {
            result += std::to_string(it) + ";";
        }
        return result.substr(0, result.size() - 1);
    }
    template<> std::string encoder::encode<std::string, nxs::header>(const std::string& v) { return v; }

    template<>
    std::string encoder::encode<std::string>(const nxs::request& req)
    {
        string str_input = "NEX:" + req._version + "/";

        // header list
        for (auto& it : req._header_list)
        {
            nxs::header& header = *it.second.get();
            str_input += header.name() + "=" + header.value_linear() + ";";
        }
        str_input += "/";

        // nex command
        string m_type = "::";
        if (req._module_type == nxs::request_base::interface) m_type = ":";
        str_input = str_input + req._module_name + m_type + req._command_name + ";";

        // param list
        for (auto& it : req._param_list)
        {
            const nxs::param& param = it.second;
            // values
            string value = "";
            for (size_t i = 0; i <  param.size(); i++)
            {
                value = value + param.value(i) + ";";
            }
            // param end
            if (value != "") str_input = str_input + param.name() + "=" + value;
        }
        // end request
        str_input += ";";
        return str_input;
    }
} // nds
