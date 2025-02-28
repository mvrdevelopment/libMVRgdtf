//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#pragma once

#include "mvrxchange_prefix.h"
#include "mvrxchange_message.h"
#include <memory>

namespace MVRxchangeNetwork
{
    struct TCPMessageInfo
    {
        uint16_t port;
        std::string ip;
    };

    class MVRxchangeClient
    {
    public:
        struct SendResult
        {
            bool success;
            boost::system::error_code error;
            TCPMessageInfo messageInfo;
            MVRxchangePacket message;
        };

        MVRxchangeClient(const MVRxchangePacket& packet, std::shared_ptr<boost::asio::io_context> io_context);
        ~MVRxchangeClient();

        SendResult SendMessage(std::chrono::steady_clock::duration timeout);
        bool Connect(SendResult& res, const std::string& host, const std::string& service, std::chrono::steady_clock::duration timeout);

    private:
        bool ReadMessage(SendResult& res, std::chrono::steady_clock::duration timeout);
        bool WriteMessage(SendResult& res, std::chrono::steady_clock::duration timeout);
        void Run(std::chrono::steady_clock::duration timeout);

        std::shared_ptr<boost::asio::io_context> fio_context;
        tcp::socket fSocket;
        const MVRxchangePacket& fMsg_send;
    };
}