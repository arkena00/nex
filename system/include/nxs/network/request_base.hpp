#ifndef NETWORK_REQUEST_BASE_H_NXS
#define NETWORK_REQUEST_BASE_H_NXS

#include <nxs/share.hpp>
#include <nxs/network/header.hpp>
#include <nxs/network/param.hpp>
#include <string>
#include <map>
#include <memory>

#undef interface

namespace nxs
{
    class NXS_SHARED request_base
    {
    public:
        enum module_typec { unknown, module, interface };
        using header_list = std::map<nxs::header::code, std::shared_ptr<nxs::header>>;

        module_typec module_type() const;
        const std::string& module_name() const;
        const std::string& command_name() const;
        const std::string full_command_name() const;

        size_t header_count() const;
        template<class H> bool header_exist() const;
        bool header_exist(nxs::header::code id) const;
        void header_exist_check(nxs::header::code id) const;
        template<class H> void header_exist_check() const;

        template<class H> void header_add();
        template<class H, class T> void header_add(T value);

        template<class H> H& header();
        nxs::header& header(nxs::header::code id) const;
        const header_list& header_get() const;

        template<class H> auto header_value(size_t index) const;
        template<class H> auto header_value() const;

    protected:
        request_base();
        request_base(module_typec module_type, const std::string& module_name, const std::string& command_name);

        module_typec _module_type;
        std::string _module_name;
        std::string _command_name;
        header_list _header_list;
        nxs::param_list _param_list;
    };
} // nxs

#include "request_base.tcc"

#endif // NETWORK_REQUEST_BASE_H_NXS

