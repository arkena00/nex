//! \file nex.cpp
//! \brief nex protocol
//! \author ads
//! \date 2016-05-16

//! new input start when all previous data received or previous input marked as finish
//! execute input when receiving data (can be changed by command)
//! send output if all data received or input marked as finish

//! NEX:1.0/header_param=header_value;/module::command;param=value; ;

#include <nxs/network/protocol/nex.hpp>
#include <nxs/network/connexion.hpp>
#include <nxs/network/buffer.hpp>
#include <nxs/core.hpp>
#include <nxs/error.hpp>
#include <fstream>

namespace nxs{namespace network
{
    nex::nex(network::connexion* cnx) :
        protocol(cnx)
    {}

    // read
    void nex::read()
    {
        try {
        // process new request
        if (input().is_finished() || input().data_complete())
        {
            input().set(std::string(connexion().buffer().data(), connexion().buffer().size()));
            output().set("nxs::response;");
            input().validate();
            input_complete(true); // data complete, can be changed by headers
            header::preprocess_all(*this);
        }
        header::process_all(*this);
        process();

        } catch (const std::exception& e) { error_send(e.what()); }
    }

    void nex::send(const request& req)
    {
        std::string str_request = nds::encoder::encode<std::string>(req);
        // send request
        connexion().send(str_request.c_str(), str_request.size());

        // send all data
        for (size_t i = 0; i< req.data_count(); i++)
        {
            const network::data& output_data = req.data_const(i);
            // send data
            if (output_data.target() == network::data::memory)
            {
                connexion().send(output_data.get<std::string>().c_str(), output_data.size());
            }
            else
            {
                std::ifstream file(output_data.get<std::string>(), std::ios::binary | std::ios::in);
                if (!file.is_open()) nxs_error << "data_hdd_read";
                std::array<char, 1024> buffer;
                while (!file.eof())
                {
                    file.read(buffer.data(), 1024);
                    connexion().send(buffer.data(), file.gcount());
                }
                file.close();
            }
        }
    }
}} // nxs::network
