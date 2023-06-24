//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------
#pragma once

#include "mvrxchange_prefix.h"

namespace MVRxchangeNetwork
{
    class MVRxchangeSession : public std::enable_shared_from_this<MVRxchangeSession>
    {
    public:
        MVRxchangeSession(tcp::socket socket);
    
    public:
        void            Start();
        virtual void    Deliver(const MVRxchangeMessage& msg);


    private:
        void DoReadHeader();
        void DoReadBody();
        void DoWrite();


        tcp::socket                     fSocket;
        MVRxchangeMessage               freadmsg;
        MVRxchangeMessageDeque          fwrite_msgs;
        std::mutex                      fwrite_msgs_mutex;
    };

}