//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#pragma once

#include "mvrxchange_prefix.h"
#include "mvrxchange_message.h"

namespace MVRxchangeNetwork
{
    class MVRxchangeServer
    {
    public:
        MVRxchangeServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint, CMVRxchangeServiceImpl* impl);

    public:            
        virtual void    Deliver(const MVRxchangePacket& msg);
        uint16_t        GetPort() const;
        uint32_t        GetIP() const;

    private:
        void DoAccept();

        CMVRxchangeServiceImpl*         fImpl;
        tcp::acceptor                   fAcceptor;
        uint16_t                        fPort;
        uint32_t                        fIp;

    };
}