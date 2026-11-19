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
        MVRxchangeServer(CMVRxchangeServiceImpl* impl);
        ~MVRxchangeServer();

        uint16_t        GetPort() const;
        uint32_t        GetIP() const;
        void AddSession(const std::shared_ptr<MVRxchangeSession>&);
        void CloseSession(const std::shared_ptr<MVRxchangeSession>&);
        inline bool isRunning() const { return !fContext.stopped(); }

    private:
        void DoAccept();
        void ExecutionFunction();
        void CloseAllSessions();

        CMVRxchangeServiceImpl*         fImpl;

        // Declared before fContext so they outlive it; pending handlers destroyed
        // during the io_context shutdown may still release sessions.
        std::mutex                                   mSession;
        std::set<std::shared_ptr<MVRxchangeSession>> fSession;

        tcp::endpoint                   fEndpoint;
		boost::asio::io_context 	    fContext;
        tcp::acceptor                   fAcceptor;

		std::thread						fExecutionThread;

        uint16_t                        fPort;
        uint32_t                        fIp;
    };
}