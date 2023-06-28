//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------
#pragma once

#include "mvrxchange_prefix.h"
#include "mvrxchange_message.h"


namespace MVRxchangeNetwork
{
    class MVRxchangeSession : public std::enable_shared_from_this<MVRxchangeSession>
    {
    public:
        MVRxchangeSession(tcp::socket socket, CMVRxchangeServiceImpl* impl);
    
    public:
        void            Start();
        virtual void    Deliver(const MVRxchangePacket& msg);


    private:
        void DoReadHeader();
        void DoReadBody();
        void DoWrite();

        CMVRxchangeServiceImpl*         fImpl;
        tcp::socket                     fSocket;
        MVRxchangePacket                freadmsg;
        MVRxchangePacketDeque           fwrite_msgs;
        std::mutex                      fwrite_msgs_mutex;
    };

}