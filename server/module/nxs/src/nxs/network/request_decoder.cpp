#include <nxs/network/request.hpp>
#include <nds/encoder.hpp>
#include <nds/data.hpp>
#include <nxs/network/header.hpp>

namespace nds
{
    template<> size_t encoder::decode<size_t, nxs::header>(const std::string& v) { return std::stoi(v); }
    template<> std::string encoder::decode<std::string, nxs::header>(const std::string& v) { return v; }

    template<>
    void encoder::decode(const std::string& str_request, nxs::request& req)
    {
        try {
        size_t version_start = str_request.find(':') + 1;
        size_t version_end = str_request.find('/');
        size_t header_start = version_end + 1;
        size_t header_end = str_request.find('/', header_start);
        size_t request_start = header_end + 1;
        size_t request_end = str_request.find(";;");
        if (request_end == std::string::npos) nxs_error << "end of request not found" << str_request;
        req._size = request_end + 2;

        req._version = str_request.substr(version_start, version_end - version_start);
        std::string str_header = "";
        if (header_end == std::string::npos) str_header = "";
        else str_header = str_request.substr(header_start, header_end - version_end - 1);

////////////////////////////////////////////////////////////////////////////////
////////////////////////             HEADER             ////////////////////////
////////////////////////////////////////////////////////////////////////////////
        size_t item_start = 0, item_end = 0;
        size_t value_start = 0, value_end = 0;
        bool read_item_name = true;
        std::string item_name = "", item_value = "";
        nxs::header::code hid;

        for (size_t i = 0; i != str_header.size(); i++)
        {
            if (str_header.at(i) == '=' && read_item_name)
            {
                read_item_name = false;

                item_end = i;
                value_start = item_end + 1;
                item_name = str_header.substr(item_start, item_end - item_start);
                std::unique_ptr<nxs::header> h = nxs::header::make(item_name);
                hid = h.get()->id();
                req._header_list.insert(std::make_pair(hid, std::move(h)));
            }
            if (str_header.at(i) == ';')
            {
                read_item_name = true;

                value_end = i;
                item_start = value_end + 1;
                item_value = str_header.substr(value_start, value_end - value_start);
                req.header(hid).add_linear(item_value);
                value_start = value_end + 1;
            }
        }

        std::string nex_command_name = str_request.substr(request_start, request_end - request_start + 1);
        nex_command_name += ";"; // add extra ; to avoid parse errors

        // parse module::command
        size_t module_command_name_end = nex_command_name.find(";");
        if (module_command_name_end != std::string::npos)
        {
            std::string module_command_name = nex_command_name.substr(0, module_command_name_end);
            // module
            size_t module_end = module_command_name.find("::", 0);
            if (module_end != std::string::npos)
            {
                req._module_name = module_command_name.substr(0, module_end);
                req._command_name = module_command_name.substr(module_end + 2, module_command_name_end);
                req._module_type = nxs::request_base::module;
            }
            // interface
            module_end = module_command_name.find(":", 0);
            if (module_end != std::string::npos && req._module_name == "")
            {
                req._module_name = module_command_name.substr(0, module_end);
                req._command_name = module_command_name.substr(module_end + 1, module_command_name_end);
                req._module_type = nxs::request_base::interface;
            }
        }

        std::string str_param = nex_command_name.substr(module_command_name_end + 1);
        if (str_param != ";") req._param_list.parse(str_param);

        } catch (const std::exception& e) { nxs_error << "header decode error :" << e.what(); }
    }
} // nds
