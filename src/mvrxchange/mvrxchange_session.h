//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------
#pragma once

#include "mvrxchange_prefix.h"
#include "mvrxchange_message.h"
#include "mvrxchange_server.h"


namespace MVRxchangeNetwork
{
    class MVRxchangeSession : public std::enable_shared_from_this<MVRxchangeSession>
    {
    public:
        MVRxchangeSession(tcp::socket socket, CMVRxchangeServiceImpl* impl, MVRxchangeServer* s);
    
    public:
        void Start();


    private:
        void DoRead();
        void Deliver(const MVRxchangePacket& msg);

        CMVRxchangeServiceImpl*         fImpl;
        MVRxchangeServer*               fServer;
        tcp::socket                     fSocket;
        MVRxchangePacket                fReadMsg;
    };

}