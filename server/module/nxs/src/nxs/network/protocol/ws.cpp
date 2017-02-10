#include <nxs/network/protocol/ws.hpp>
#include <nxs/network/connexion.hpp>
#include <nxs/network/buffer.hpp>
#include <nxs/crypto/botan.hpp>

namespace nxs{namespace network
{

    ws::ws(network::connexion* cnx) :
        protocol(cnx),
        _handshake_done(0)
    {}

    void ws::input_read(const buffer_type& buf)
    {
        // process handshake if not done
        if (!_handshake_done) return process_handshake(buf.data(), buf.size());

        // handshake ok, read data
        std::string nex_input = data_decode(buf.data(), buf.size());
        nex_input = "NEX:1.0//" + nex_input + ";";
        input().set(nex_input);

        output().set("nxs::response;");

        input_process();
    }

    void ws::output_send(const request& req)
    {

        //connexion().data_send(req.data_const(0).get<std::string>().c_str(), req.data_const(0).size());
    }

    void ws::input_send(const nxs::request& req){}

    void ws::output_read(const buffer_type&){}


    // handshake
    void ws::process_handshake(const char* raw_data, size_t data_received)
    {
        std::string data(raw_data, data_received);
        // get key
        size_t wskey_pos = data.find("Sec-WebSocket-Key:");
        size_t wskey_pos_end = data.find("\r\n", wskey_pos);
        std::string guuid = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
        std::string wskey = data.substr(wskey_pos + 19, wskey_pos_end - wskey_pos - 19);
        // accept connexion
        std::string crypt_key = wskey + guuid;
        Botan::Pipe pipe(new Botan::Hash_Filter("SHA-1"), new Botan::Base64_Encoder);
        pipe.process_msg(crypt_key);
        crypt_key = pipe.read_all_as_string();
        std::string handshake = "HTTP/1.1 101 WebSocket Protocol Handshake\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Accept: " + crypt_key + "\r\n\r\n";

        _handshake_done = 1;

        data_send(handshake.c_str(), handshake.size());
    }

    // decode data
    std::string ws::data_decode(const char* data, size_t data_received)
    {
        unsigned char* byte = (unsigned char*)data;
        unsigned char fin_rsv_opcode = byte[0];

        // get message length

        // close connection if unmasked message from client (protocol error)
        if (byte[1] < 128) nxs_error(errc::system, "NXS_PROTOCOL_WS_ERROR");

        size_t length = byte[1] & 127;
        size_t nb_byte = 0;
        // get bytes to read for size
        if (length == 126) nb_byte = 2;
        if (length == 127) nb_byte = 8;
        if (nb_byte > 0)
        {
            length = 0;
            for(size_t i = 0; i < nb_byte; i++)
            {
                // length offset = 2
                length += byte[2 + i] << (8 * (nb_byte - 1 - i));
            }
        }

        // get message
        size_t message_offset = 2 + nb_byte;
        char buffer[data_received] = {0};
        // read mask
        char mask[3] = {0};
        strncpy(mask, data + message_offset, 4);
        // decode message
        for (size_t i = 0; i < length; i++)
        {
            buffer[i] = (data + message_offset + 4)[i] ^ (unsigned char)mask[i % 4];
        }

        if((fin_rsv_opcode & 0x0f) == 8) std::cout << "\n connexion closed";
        if((fin_rsv_opcode & 0x0f) == 9) std::cout << "\n pinged by client";

        return std::string(buffer, length);
    }

    void ws::data_send(const char* data, size_t data_size)
    {
        size_t length = data_size;

        size_t nb_byte = 0;
        if (data_size >= 126) {nb_byte = 2; length = 126;}
        if (data_size > 0xffff) {nb_byte = 8; length = 127;}

        // get response size
        int header_size = 1 + 1 + nb_byte;
        int response_size = header_size + data_size;
        unsigned char response[response_size] = {0};

        response[0] = 129;
        response[1] = length;
        size_t z = 2;
        for(int i = nb_byte - 1; i >= 0; i--)
        {
            response[z++] = (data_size >> (8 * i)) % 256;
        }

        memcpy(response + header_size, data, data_size);

        // send data on socket
        connexion().data_send((char*)response, response_size);
    }
}} // nxs::network
