#include <nxs/error.hpp>
#include <nxs/network/protocol.hpp>
#include <iostream>

namespace nxs{namespace network
{
    template<io::type IO_Type>
    size_t basic_connexion<IO_Type>::id_ = 0;

    template<io::type IO_Type>
    basic_connexion<IO_Type>::basic_connexion(boost::asio::io_service& ios, std::unique_ptr<network::protocol> p) :
        _id(++id_),
        _protocol(std::move(p)),
        _alive(false),
        _socket(ios)
    {}


    template<io::type IO_Type>
    void basic_connexion<IO_Type>::socket_send(const boost::system::error_code& status, size_t bytes_transferred)
    {
        if (!status && _alive)
        {
            auto& data = *_output_buffer.front().get();
            data.transfer_add(bytes_transferred);
            std::cout << "\ntransfer progress " << data.transfer_progress();
            if (data.transfer_complete())
            {
                _output_buffer.pop_front();
            }
            // keep sending data
            send();
        }
        else std::cout << "________ERROR";
    }


    template<io::type IO_Type>
    void basic_connexion<IO_Type>::send()
    {
        // all data sent
        if (_output_buffer.size() == 0) return;

        // send front data
        auto& data = *_output_buffer.front().get();

        boost::asio::async_write(_socket, boost::asio::buffer(data.ptr(), data.size()),
                             boost::bind(&basic_connexion<IO_Type>::socket_send, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred)
        );
    }

    template<io::type IO_Type>
    void basic_connexion<IO_Type>::send(network::data_ptr d)
    {
        bool start_send = false;
        if (_output_buffer.size() == 0) start_send = true;
        _output_buffer.push_back(d);
        // start to send data if output data was empty
        if (start_send) send();
    }


    template<io::type IO_Type>
    void basic_connexion<IO_Type>::send(const std::string& data)
    {
        send(data.c_str(), data.size());
    }

    template<io::type IO_Type> size_t basic_connexion<IO_Type>::id() const { return _id; }
    template<io::type IO_Type> constexpr io::type basic_connexion<IO_Type>::iotype() const { return IO_Type; }
    template<io::type IO_Type> bool basic_connexion<IO_Type>::is_alive() const { return _alive; }
    template<io::type IO_Type> typename basic_connexion<IO_Type>::buffer_type& basic_connexion<IO_Type>::buffer() { return _buffer; }

    template<io::type IO_Type>
    network::protocol& basic_connexion<IO_Type>::protocol()
    {
        if (_protocol.get() == nullptr) nxs_error << log::system;
        return *_protocol.get();
    }

    template<io::type IO_Type>
    template<class Protocol>
    void basic_connexion<IO_Type>::protocol_set()
    {
        auto p = protocol::create<Protocol>(*this);
        _protocol.swap(p);
    }

    template<io::type IO_Type>
    bool basic_connexion<IO_Type>::has_protocol() const
    {
        if (_protocol.get() == nullptr) return false;
        return true;
    }

    template<io::type IO_Type>
    boost::asio::ip::tcp::socket& basic_connexion<IO_Type>::socket() { return _socket; }
}} // nxs::network
