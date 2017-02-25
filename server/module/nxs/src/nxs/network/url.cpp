#include <nxs/network/url.hpp>

namespace nxs{namespace network
{
    url::url() : _url("nex://127.0.0.1:50"),
        _host("localhost"),
        _port(50),
        _protocol("nex"),
        _command("")
    {}

    url::url(const std::string& url) : url::url()
    {
        size_t host_pos = 0;
        // protocol
        size_t prot_pos = url.find("://");
        if (prot_pos != std::string::npos)
        {
            host_pos = prot_pos + 3;
            _protocol = url.substr(0, prot_pos);
        }
        // url is a command
        else
        {
            _host = "";
            _command = url;
            return;
        }

        // command
        size_t command_pos = url.find("/", host_pos + 1);
        if (command_pos != std::string::npos) _command = url.substr(command_pos + 1);

        // host
        _host = url.substr(host_pos, command_pos - host_pos);

        // host:port
        size_t port_pos = _host.find(":");
        if (port_pos != std::string::npos)
        {
            _port = std::stoi(_host.substr(port_pos + 1));
            _host = _host.substr(0, port_pos);
        }
    }

    const std::string& url::str() const { return _url; }
    const std::string& url::protocol() const { return _protocol; }
    const std::string& url::host() const { return _host; }
    uint16_t url::port() const { return _port; }
    const std::string& url::command() const { return _command; }

}} // nxs::network
