//! \file nex.cpp
//! \brief nex protocol
//! \author ads
//! \date 2016-05-16

//! new input start when all previous data received or previous input marked as finish
//! execute input when receiving data (can be changed by command)
//! send output if all data received or input marked as finish

#include <nxs/network/protocol/nex.hpp>
#include <nxs/network/connexion.hpp>
#include <nxs/network/buffer.hpp>
#include <nxs/core/nxs.hpp>
#include <nxs/core/error.hpp>
#include <fstream>

namespace nxs{namespace network
{
    nex::nex(network::connexion* cnx) :
        protocol(cnx)
    {}

    void nex::input_read(const buffer_type& buf)
    {
        try {
        // process new request
        if (input().is_finished() || input().data_complete())
        {
            input().set(std::string(buf.data(), buf.size()));
            output().set("nxs::response;");
            input().validate();
            input_complete(true); // data complete, can be changed by headers
            header::preprocess_all(*this);
        }
        header::process_all(*this);
        input_process();

        } catch (const std::exception& e) { return error_send(e.what()); }
    }

    void nex::input_send(const request&) {}
    void nex::output_read(const buffer_type& buf) {}

    void nex::output_send(const request& req)
    {
        std::string str_request = nds::encoder::encode<std::string>(req);
        // send request
        connexion().data_send(str_request.c_str(), str_request.size());

        // send all data
        for (size_t i = 0; i< req.data_count(); i++)
        {
            const network::data& output_data = req.data_const(i);
            // send data
            if (output_data.target() == network::data::memory)
            {
                connexion().data_send(output_data.get<std::string>().c_str(), output_data.size());
            }
            else
            {
                std::ifstream file(output_data.get<std::string>(), std::ios::binary | std::ios::in);
                if (!file.is_open()) nxs_error(errc::data_hdd_read);
                std::array<char, 1024> buffer;
                while (!file.eof())
                {
                    file.read(buffer.data(), 1024);
                    connexion().data_send(buffer.data(), file.gcount());
                }
                file.close();
            }
        }
    }
}} // nxs::network
