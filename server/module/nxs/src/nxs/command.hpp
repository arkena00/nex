#ifndef COMMAND_H_NXS
#define COMMAND_H_NXS

#include <nxs/share.hpp>
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
        using Command_List = std::map<std::string, command>;

    private:
        static Command_List list_;

        int _id;
        nxs::param_list _param_list;
        std::function<void(nxs::nex&)> _address;
        std::string _help;
        bool _wait_transfer;

    public:
        enum code { nxs = 0, resource, type, file, user, module, interface, size_ };

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

        static command& add(const std::string& module, const std::string& name, std::function<void(nxs::nex&)> fn);
        static const Command_List& get();
        static const command& get(const std::string& full_command);
        static bool exist(const std::string& full_command);
        static void init();

        template<unsigned char C = 0>
        static void initialize();

        template<unsigned char C = 0>
        static void init_loop()
        {
            command::initialize<C>();
            init_loop<C + 1>();
        }
    };
} // nxs

#endif // COMMAND_H_NXS
