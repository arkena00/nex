//! \file nex.cpp
//! \brief nex protocol
//! \author ads
//! \date 2016-05-16

//! new input start when all previous data received or previous input marked as finish
//! execute input when receiving data (can be changed by command)
//! send output if all data received or input marked as finish

//! NEX:1.0/header_param=header_value;/module::command;param=value; ;

#include <nxs/network/protocol/nex.hpp>
#include <nxs/network/connexion/basic.hpp>
#include <nxs/network/buffer.hpp>
#include <nxs/core.hpp>
#include <nxs/error.hpp>
#include <fstream>

namespace nxs{namespace network
{
    // read
    template<io::type IO_Type>
    void nex<IO_Type>::read()
    {
        using Protocol = basic_protocol<IO_Type>;

        try {
        // process new request
        if (Protocol::process_complete() || Protocol::transfer_complete())
        {
            Protocol::input().set(std::string(Protocol::connexion().buffer().data(), Protocol::connexion().buffer().size()));
            Protocol::output().set("nxs::response;");
            Protocol::input().validate();
            Protocol::process_complete(false); // process not completed, can be changed by commands to terminate a request
            Protocol::transfer_complete(true); // data complete, can be changed by headers
            header::preprocess_all(*this);
        }
        header::process_all(*this);
        Protocol::process();

        } catch (const std::exception& e) { Protocol::error(e.what()); }
    }

    template<io::type IO_Type>
    void nex<IO_Type>::send(const request& req)
    {
        using Protocol = basic_protocol<IO_Type>;

        std::string str_request = nds::encoder::encode<std::string, nds::encoders::global>(req);
        // send request
        Protocol::connexion().send(str_request.c_str(), str_request.size());

        // send all data
        for (size_t i = 0; i< req.data_count(); i++)
        {
            const network::data& output_data = req.data_const(i);
            // send data
            if (output_data.target() == network::data::memory)
            {
                Protocol::connexion().send(output_data.get<std::string>().c_str(), output_data.size());
            }
            else
            {
                std::ifstream file(output_data.get<std::string>(), std::ios::binary | std::ios::in);
                if (!file.is_open()) nxs_error << "data_hdd_read";
                std::array<char, 1024> buffer;
                while (!file.eof())
                {
                    file.read(buffer.data(), 1024);
                    Protocol::connexion().send(buffer.data(), file.gcount());
                }
                file.close();
            }
        }
    }
}} // nxs::network
