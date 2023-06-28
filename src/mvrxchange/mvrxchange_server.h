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
        virtual void Deliver(const MVRxchangeMessage& msg);
        short GetPort() const;

    private:
        void DoAccept();

        CMVRxchangeServiceImpl*         fImpl;
        tcp::acceptor                   fAcceptor;
        short                           fPort;

    };
}