#ifndef COMMAND_COMMAND_H_NXS
#define COMMAND_COMMAND_H_NXS

#include <nxs/os/share.hpp>
#include <nxs/core/constant.hpp>
#include <nxs/network/request_base.hpp>
#include <nxs/network/param.hpp>
#include <map>
#include <functional>

namespace nxs
{
    class nex;
    class request;
    template<unsigned char> struct commands {};

    class NXS_SHARED command : public request_base
    {
    private:
        static std::map<std::string, command> list_;

        int _id;
        nxs::param_list _param_list;
        std::function<void(nxs::nex&)> _address;
        std::string _help;
        bool _wait_transfer;

    public:
        enum code { nxs = 0, file, user, size_ };

        command(const std::string& module, const std::string& name, std::function<void(nxs::nex&)> fn);

        int id() const;
        const nxs::param_list& param_list() const;
        const std::function<void(nxs::nex&)>& address() const;
        const std::string& help() const;
        void help_set(const std::string& text);
        void wait_transfer(bool n);
        bool wait_transfer() const;


        void execute(nxs::nex&) const;
        void check(nxs::request& req) const;
        void param_add(const std::string& name,
                       const param::modc& = param::modc::require,
                       const std::string& default_value = "",
                       const std::string& format = "");

        static std::map<std::string, command>& list();
        static command& add(const std::string& module, const std::string& name, std::function<void(nxs::nex&)> fn);
        static const command& get(const std::string& full_command);
        static bool exist(const std::string& full_command);
        static void load();

        template<unsigned char C = 0>
        static void init();

        template<unsigned char C = 0>
        constexpr static void init_all()
        {
            command::init<C>();
            init_all<C + 1>();
        }
    };

    template<>
    constexpr void command::init_all<command::size_>() {}

} // nxs

#endif // COMMAND_COMMAND_H_NXS
