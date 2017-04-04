#ifndef NETWORK_CONNEXION_BASIC_OUTPUT_H_NXS
#define NETWORK_CONNEXION_BASIC_OUTPUT_H_NXS

#include <nxs/network/socket.hpp>
#include <nxs/network/connexion/basic.hpp>
#include <nxs/network/connexion/output.hpp>
#include <nxs/network/connexion/manager.hpp>

namespace nxs{namespace network
{
    template<class Protocol>
    class NXS_SHARED basic_output_connexion : public basic_connexion<io::output>, public output_connexion
    {
    private:
        connexion_manager<output_connexion>& _client;

        boost::asio::deadline_timer _timer;

        std::function<void()> _on_connect;

    public:
        basic_output_connexion(connexion_manager<output_connexion>&);

        virtual void on_connect(std::function<void()>) override;

        void connect(const std::string& ip, uint16_t port, int time_out = 5) override;

        void sync_connect(const std::string& ip, uint16_t port);
        void sync_read();
    };
}} // nxs::network

#include "basic_output.tcc"

#endif // NETWORK_CONNEXION_BASIC_OUTPUT_H_NXS
