#ifndef NETWORK_URL_H_NXS
#define NETWORK_URL_H_NXS

#include <nxs/os/share.hpp>
#include <string>

namespace nxs{namespace network
{
    class NXS_SHARED url
    {
    private:
        std::string _url;
        std::string _host;
        uint16_t _port;
        std::string _protocol;
        std::string _command;

    public:
        url();
        url(const std::string&);
        url(const url&) = default;

        const std::string& str() const;
        const std::string& protocol() const;
        const std::string& host() const;
        uint16_t port() const;
        const std::string& command() const;
    };
}} // nxs::network

#endif // NETWORK_URL_H_NXS
