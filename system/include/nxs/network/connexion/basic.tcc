#include <nxs/error.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/network/protocol/nex.hpp>
#include <nxs/network/protocol/http.hpp>
#include <iostream>

namespace nxs{namespace network
{
    template<io::type IO_Type>
    basic_connexion<IO_Type>::basic_connexion(boost::asio::io_service& ios, std::unique_ptr<network::protocol> p) :
        _id((size_t)reinterpret_cast<void*>(this)),
        _protocol(std::move(p)),
        _alive(false),
        _socket(ios),
        _output_progress_size(setup<connexion>::output_progress_size)
    {}

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::read()
    {
        if (!_alive) return;

        auto socket_read = [this](const boost::system::error_code& err, std::size_t transfer_size)
        {
            if (!_alive) return;
            if (!err)
            {
                buffer().reserve(transfer_size);
                try
                {
                    if (IO_Type == io::input) protocol_detect();
                    protocol().read();

                    if (_on_read) _on_read();
                    // read next data
                    read();
                } catch (const std::exception& e)
                {
                    nxs_log << e.what() << log::network;
                    close();
                }
            }
            else error(err);
        };

        _socket.async_read_some(boost::asio::buffer(_buffer.address(), _buffer.capacity()), socket_read);
    }

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::send()
    {
        // all data sent
        if (_output_data.size() == 0) return;

        // send front data
        auto& data = *_output_data.front().get();

        auto progress = [this, &data](const boost::system::error_code& err, std::size_t transfer_size) -> std::size_t
        {
            data.transfer_set(transfer_size);
            if (_on_send) _on_send(data);
            return err ? 0 : _output_progress_size;
        };
        auto data_complete = [this, &data](const boost::system::error_code& err, std::size_t transfer_size)
        {
            if (!err && _alive)
            {
                _output_data.pop_front();
                // send next data
                send();
            }
            else error(err);
        };

        boost::asio::async_write(_socket, boost::asio::buffer(data.ptr(), data.size()), progress, data_complete );
    }

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::send(network::data_ptr d)
    {
        bool start_send = false;
        if (_output_data.size() == 0) start_send = true;
        _output_data.push_back(d);
        // start to send data if output buffer queue was empty
        if (start_send) send();
    }

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::error(const boost::system::error_code& err)
    {
        _alive = false;
        if (_on_error) _on_error(err.message());
        close();
    }

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::close()
    {
        if (_alive)
        {
            _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            _socket.close();
        }
        _alive = false;
        if (_on_close) _on_close();
        nxs_log << "connexion closed " << _id << log::network;
    }

    template<io::type IO_Type>
    template<class Protocol>
    void basic_connexion<IO_Type>::protocol_set()
    {
        auto p = protocol::create<Protocol>(*this);
        _protocol.swap(p);
    }

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::protocol_detect()
    {
        if (has_protocol()) return;

        // nex
        if (strncmp(_buffer.data(), "NEX", 3) == 0) protocol_set<nex<io::input>>();
            // http
        else if (strncmp(_buffer.data(), "GET", 3) == 0 || strncmp(_buffer.data(), "POST", 4) == 0)
        {
            // ws
            std::string str_data = std::string(_buffer.data(), _buffer.size());
            // if (str_data.find("Sec-WebSocket-Key:") != std::string::npos) protocol_set<ws>();
            protocol_set<http<io::input>>();
        }
            // no protocol found, disconnect
        else nxs_error << "protocol_unknown\n" << std::string(_buffer.data(), _buffer.size());
    }

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::on_read(std::function<void()> fn)
    {
        _on_read = fn;
    }

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::on_send(std::function<void(const network::data&)> fn, std::size_t progress_size)
    {
        _output_progress_size = progress_size;
        _on_send = fn;
    }

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::on_error(std::function<void(const std::string&)> fn)
    {
        _on_error = fn;
    }

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::on_close(std::function<void()> fn)
    {
        _on_close = fn;
    }

    template<io::type IO_Type>
    size_t basic_connexion<IO_Type>::id() const
    {
        return _id;
    }

    template<io::type IO_Type>
    constexpr io::type basic_connexion<IO_Type>::iotype() const
    {
        return IO_Type;
    }

    template<io::type IO_Type>
    bool basic_connexion<IO_Type>::is_alive() const
    {
        return _alive;
    }

    template<io::type IO_Type>
    typename basic_connexion<IO_Type>::buffer_type &basic_connexion<IO_Type>::buffer()
    {
        return _buffer;
    }

    template<io::type IO_Type>
    std::string basic_connexion<IO_Type>::ip() const
    {
        return _socket.remote_endpoint().address().to_string();
    }

    template<io::type IO_Type>
    uint16_t basic_connexion<IO_Type>::port() const
    {
        return _socket.remote_endpoint().port();
    }

    template<io::type IO_Type>
    network::protocol& basic_connexion<IO_Type>::protocol()
    {
        if (_protocol.get() == nullptr) nxs_error << log::system;
        return *_protocol.get();
    }

    template<io::type IO_Type>
    bool basic_connexion<IO_Type>::has_protocol() const
    {
        if (_protocol.get() == nullptr) return false;
        return true;
    }
/*
    template<io::type IO_Type>
    boost::asio::ip::tcp::socket &basic_connexion<IO_Type>::socket()
    {
        return _socket;
    }*/
}} // nxs::network