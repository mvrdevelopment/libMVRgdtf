//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#pragma once

#include "mvrxchange_prefix.h"
#include "mvrxchange_message.h"

namespace MVRxchangeNetwork
{
    class MVRxchangeClient
    {
    public:
    MVRxchangeClient(CMVRxchangeServiceImpl* impl, const MVRxchangePacket& packet);
    ~MVRxchangeClient();

    bool            Connect(const std::string& host, const std::string& service, std::chrono::steady_clock::duration timeout);
    bool            ReadMessage(std::chrono::steady_clock::duration timeout);
    bool            WriteMessage(std::chrono::steady_clock::duration timeout);

    private:
    void Run(std::chrono::steady_clock::duration timeout);

    boost::asio::io_context   fio_context;
    tcp::socket               fSocket{fio_context};
    const MVRxchangePacket&   fMsg_send;
    MVRxchangePacket          fMsg_ret;
    CMVRxchangeServiceImpl*   fImpl;
};
}