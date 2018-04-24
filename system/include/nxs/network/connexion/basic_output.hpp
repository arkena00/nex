#ifndef NETWORK_CONNEXION_BASIC_OUTPUT_H_NXS
#define NETWORK_CONNEXION_BASIC_OUTPUT_H_NXS
#pragma warning(push)
#pragma warning(disable : 4250)

#include <nxs/network/socket.hpp>
#include <nxs/network/connexion/basic.hpp>
#include <nxs/network/connexion/output.hpp>
#include <nxs/network/connexion/manager.hpp>

namespace nxs{namespace network
{
    template<class Protocol>
    class basic_output_connexion : public basic_connexion<io::output>, public output_connexion
    {
    private:
        asio::steady_timer _timer;

        std::function<void()> _on_connect;

    public:
        basic_output_connexion(asio::io_service&);

        void on_connect(std::function<void()>) override;

        void connect(const std::string& ip, uint16_t port, int time_out = 5) override;

        void sync_connect(const std::string& ip, uint16_t port);
        void sync_read();
    };
}} // nxs::network

#include "basic_output.tcc"

#pragma warning(pop)
#endif // NETWORK_CONNEXION_BASIC_OUTPUT_H_NXS
