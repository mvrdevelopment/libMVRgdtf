//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#pragma once

#include "mvrxchange_prefix.h"
#include "mvrxchange_message.h"

namespace MVRxchangeNetwork
{
    class MVRxchangeSession;
    class MVRxchangeServer
    {
    public:
        MVRxchangeServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint, CMVRxchangeServiceImpl* impl);

    public:            
        uint16_t        GetPort() const;
        uint32_t        GetIP() const;


        void AddSession(std::shared_ptr<MVRxchangeSession>);
        void CloseSession(std::shared_ptr<MVRxchangeSession>);

    private:
        void DoAccept();

        CMVRxchangeServiceImpl*         fImpl;
        std::mutex                                   mSession;
        std::set<std::shared_ptr<MVRxchangeSession>> fSession;
        tcp::acceptor                   fAcceptor;
        uint16_t                        fPort;
        uint32_t                        fIp;

    };
}